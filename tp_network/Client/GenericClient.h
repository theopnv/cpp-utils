#pragma once

#include <deque>
#include <memory>
#include "asio.hpp"
#include "Message.h"
#include "typedefs.h"
#include "PacketBuild.h"

namespace tp_network
{
	/*
	* Don't use this class to handle your connections, always use
	* the upper-level "Client" class (Client.h) !
	* Must be provided with :
	* 	- ioService
	* 		--> See boost Asio documentation for further information
	* 	- newMessageReadCallback
	* 		--> Will be called when a packet is read on the socket
	*/
	class GenericClient
	{

	  public:
		GenericClient(asio::io_service& ioService,
					  Event<void (const std::string&)> newMessageReadCallback) :
			_ioService(ioService),
			_socket(ioService),
			_newMessageReadCallback(newMessageReadCallback)
		{
		}

		~GenericClient()
		{
			close();
		}

		void start()
		{
			doConnect(_endpointIterator);
		}

		bool write(std::string& packet)
		{
			std::size_t idx = 0;

			// Header
			int excedent = (int)packet.length() % Message::max_body_length == 0 ? 0 : 1;
			int totalMsgInPacket = ((int)packet.length() / Message::max_body_length) + excedent;
			Message header(totalMsgInPacket);
			bool writeInProgress = !_writeQueue.empty();
			_writeQueue.emplace_back(header);
			if (!writeInProgress) {
				doWrite();
			}

			// Content
			do {

				Message body(packet.substr(idx, Message::max_body_length));

				bool writeInProgress = !_writeQueue.empty();
				_writeQueue.emplace_back(body);
				if (!writeInProgress) {
					doWrite();
				}

				idx += Message::max_body_length;

			} while (idx < packet.length());

			return true;

		}

		void close()
		{
			_ioService.post(
				[this]()
			{
				_socket.close();
			});
		}

		void setEndpointIterator(const tcp::resolver::iterator& eI)
		{
			_endpointIterator = eI;
		}

	  private:
		asio::io_service&	_ioService;
		tcp::socket			_socket;
		tcp::resolver::iterator 	_endpointIterator;

		PacketBuild			_packetBuild;

		Message				_currentMessage;
		MessageQueue		_writeQueue;
		Event<void (const std::string&)>	_newMessageReadCallback;

		void doConnect(tcp::resolver::iterator endpointIterator)
		{
			asio::async_connect(_socket, endpointIterator,
				[this](std::error_code ec, tcp::resolver::iterator)
			{
				if (!ec) {
					doReadHeader();
				}
			});
		}

		void doReadHeader()
		{
			asio::async_read(_socket,
				asio::buffer(_currentMessage.getData(), Message::header_length),
				[this](std::error_code ec, std::size_t /*length*/)
			{
				if (!ec && _currentMessage.decodeHeader()) {
					doReadBody();
				}
				else {
					close();
				}
			});
		}

		void doReadBody()
		{
			asio::async_read(_socket,
				asio::buffer(_currentMessage.getBody(), _currentMessage.getSizeHeaderInfo()),
				[this](std::error_code ec, std::size_t /* length */)
			{
				if (!ec) {
					if (_currentMessage.getTypeHeaderInfo() == Message::header) {
						_packetBuild = PacketBuild(std::atoi(_currentMessage.getBody()));
					}
					else {
						_packetBuild._data += _currentMessage.getBody();
					}

					++_packetBuild._currentMsgIdx;

					if (_packetBuild._currentMsgIdx >= _packetBuild._expectedMsgCount) {
						_newMessageReadCallback(_packetBuild._data);
					}

					doReadHeader();
				}
			});
		}

		void doWrite()
		{
			std::size_t msgSize = std::strlen(_writeQueue.front().getData()) + 1;
			asio::async_write(_socket,
				asio::buffer(_writeQueue.front().getData(), msgSize),
				[this](std::error_code ec, std::size_t /* length */)
			{
				if (!ec) {
					_writeQueue.pop_front();
					if (!_writeQueue.empty()) {
						doWrite();
					}
				}
				else {
					close();
				}
			});
		}

	};

}
