#pragma once

#include <iostream>
#include "asio.hpp"
#include "typedefs.h"
#include "Message.h"
#include "PacketBuild.h"

namespace tp_network
{

	/*
	 * A session represents a client connection.
	 * It has a unique id (Boost UUID) for client identification.
	 * Must be provided with :
	 * 	- socket
	 * 		--> The socket it must read from and write onto
	 * 	- packet read callback
	 * 		--> Will be called when a new packet is read on the socket
	 */
	class Session : public std::enable_shared_from_this<Session>
	{

	  public:
		Session(tcp::socket socket,
				Event<void (const std::string&, const std::string&)> newMessageReadCallback) :
			_socket(std::move(socket)),
			_newMessageReadCallback(newMessageReadCallback)
		{
		}

		/*
		 * Start the session.
		 */
		void start()
		{
			doReadHeader();
		}

		/*
		 * Write a packet on the socket
		 */
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

		/*
		 * Set the unique id of the session
		 */
		void setId(const std::string& id)
		{
			_id = id;
		}

	  private:
		tcp::socket			_socket;

		Message				_currentMessage;
		MessageQueue		_writeQueue;
		PacketBuild			_packetBuild;

		std::string			_id;
		Event<void (const std::string&, const std::string&)>	_newMessageReadCallback;

		void doReadHeader()
		{
			asio::async_read(_socket,
							 asio::buffer(_currentMessage.getData(), Message::header_length),
							 [this](std::error_code ec, std::size_t /*length*/)
							 {
								 if (!ec && _currentMessage.decodeHeader())
								 {
									 doReadBody();
								 }
							 });
		}

		void doReadBody()
		{
			asio::async_read(_socket,
							 asio::buffer(_currentMessage.getBody(), _currentMessage.getSizeHeaderInfo()),
							 [this](std::error_code ec, std::size_t /*length*/)
							 {
								 if (!ec)
								 {
								 	if (_currentMessage.getTypeHeaderInfo() == Message::header) {
								 		_packetBuild = PacketBuild(std::atoi(_currentMessage.getBody()));
								 	} else {
								 		_packetBuild._data += _currentMessage.getBody();
								 	}

								 	++_packetBuild._currentMsgIdx;

								 	if (_packetBuild._currentMsgIdx >= _packetBuild._expectedMsgCount) {
										_newMessageReadCallback(_id, _packetBuild._data);
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
							  [this](std::error_code ec, std::size_t /*length*/) {
								  if (!ec) {
									  _writeQueue.pop_front();
									  if (!_writeQueue.empty()) {
										  doWrite();
									  }
								  }
							  });
		}

	};

	using SessionSP = std::shared_ptr<Session>;

}