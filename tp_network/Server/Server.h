//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include <map>
#include <functional>
#include <thread>
#include "asio.hpp"
#include "sole/sole.hpp"
#include "tp_network.h"
#include "GenericServer.h"

namespace tp_network
{

	/**
	 * \brief Server class
	 * Should be started in a separated thread 
	 */
	class Server
	{

	  public:
		/**
		 * \brief 
		 * \param newConnectionCallbackExternal Will be called when a new client just got accepted
		 * \param newMessageReadCallback Will be called when a packet is read on the socket
		 * \param port The port you want the server to listen onto
		 */
		Server(const Event<void (const std::string&)> newConnectionCallbackExternal,
		       const Event<void (const std::string&, const std::string&)> newMessageReadCallback,
		       const unsigned short port) :
			_newConnectionCallbackExternal(newConnectionCallbackExternal),
			_newMessageReadCallback(newMessageReadCallback),
			_port(port)
		{
		}

		~Server()
		{
			_networkThread.join();
		}

		/**
		 * \brief Start the server.
		 */
		void run()
		{
			try {
				const auto newConnectionCallbackInternal = std::bind(&Server::newConnectionCallbackInternal, this, std::placeholders::_1);

				asio::io_service ioService;

				const tcp::endpoint endpoint(tcp::v4(), _port);
				auto server = GenericServer(
					ioService,
					endpoint,
					newConnectionCallbackInternal,
					_newMessageReadCallback);

				ioService.run();

			} catch (std::exception& e) {
				std::cerr << "Exception: " << e.what() << std::endl;
			}
		}

		/**
		 * \brief Send a message to a specific client
		 * \param uuid The client's Id the message is to be sent to
		 * \param packet The object to send. Must be serializable through the IJsonSerializable interface.
		 */
		void send(const std::string& uuid, std::string& packet)
		{
			auto client = _clients.at(uuid);
			if (client) {
				client->write(packet);
			}
		}

	  private:

		Event<void (const std::string&)>	_newConnectionCallbackExternal;
		Event<void (const std::string&, const std::string&)>	_newMessageReadCallback;
		unsigned short						_port;
		std::map<std::string, SessionSP>	_clients;
		std::thread							_networkThread;

		void newConnectionCallbackInternal(SessionSP session)
		{
			auto uuid = sole::uuid0();
			auto id = uuid.str();

			_clients.insert(std::make_pair(id, session));

			session->setId(id);

			_newConnectionCallbackExternal(id);
		}
	};

}
