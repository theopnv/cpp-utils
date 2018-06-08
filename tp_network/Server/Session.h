//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include "asio.hpp"
#include "tp_network.h"
#include "Message.h"
#include "PacketBuild.h"

namespace tp_network
{

	/**
	 * \brief A session represents a client connection.
	 * It has a unique id (Boost UUID) for client identification.
	 */
	class Session : public std::enable_shared_from_this<Session>
	{

	  public:
		/**
		 * \brief 
		 * \param socket The socket it must read from and write onto
		 * \param newMessageReadCallback Will be called when a new packet is read on the socket
		 */
		Session(tcp::socket socket,
		        const Event<void (const std::string&, const std::string&)> newMessageReadCallback) :
			_socket(std::move(socket)),
			_newMessageReadCallback(newMessageReadCallback)
		{
		}

		/**
		 * \brief Start the session.
		 */
		void start()
		{
			doReadHeader();
		}

		/**
		 * \brief Write a packet on the socket
		 * \param packet Packet to send to the associated client
		 * \return 
		 */
		bool write(std::string& packet)
		{
			std::size_t idx = 0;

			// Header
			const auto excedent = static_cast<int>(packet.length()) % Message::max_body_length == 0 ? 0 : 1;
			const auto totalMsgInPacket = (static_cast<int>(packet.length()) / Message::max_body_length) + excedent;
			Message header(totalMsgInPacket);
			const auto writeInProgress = !_writeQueue.empty();
			_writeQueue.emplace_back(header);
			if (!writeInProgress) {
				doWrite();
			}

			// Content
			do {

				Message body(packet.substr(idx, Message::max_body_length));

				auto writeInProgress = !_writeQueue.empty();
				_writeQueue.emplace_back(body);
				if (!writeInProgress) {
					doWrite();
				}

				idx += Message::max_body_length;

			} while (idx < packet.length());

			return true;

		}

		/**
		 * \brief Set the unique id of the session
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

		/**
		 * \brief Read revceived header
		 */
		void doReadHeader()
		{
			asio::async_read(_socket,
							 asio::buffer(_currentMessage.getData(), Message::header_length),
							 [this](const std::error_code ec, std::size_t /*length*/)
							 {
								 if (!ec && _currentMessage.decodeHeader())
								 {
									 doReadBody();
								 }
							 });
		}

		/**
		 * \brief After having read the header, read the content of the received message
		 */
		void doReadBody()
		{
			asio::async_read(_socket,
							 asio::buffer(_currentMessage.getBody(), _currentMessage.getSizeHeaderInfo()),
							 [this](const std::error_code ec, std::size_t /*length*/)
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

		/**
		 * \brief Actually write on the socket
		 */
		void doWrite()
		{
			const auto msgSize = std::strlen(_writeQueue.front().getData()) + 1;
			asio::async_write(_socket,
							  asio::buffer(_writeQueue.front().getData(), msgSize),
							  [this](const std::error_code ec, std::size_t /*length*/) {
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