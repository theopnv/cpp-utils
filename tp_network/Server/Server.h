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

	/*
	 * Server class
	 * Should be started in a separated thread
	 * Must be provided with :
	 * 	- connection callback
	 * 		--> Will be called when a new client just got accepted
	 * 	- packet read callback
	 * 		--> Will be called when a packet is read on the socket
	 * 	- port
	 * 		--> The port you want the server to listen onto
	 */
	class Server
	{

	  public:
		Server(Event<void (const std::string&)> newConnectionCallbackExternal,
			   Event<void (const std::string&, const std::string&)> newMessageReadCallback,
			   unsigned short port) :
			_newConnectionCallbackExternal(newConnectionCallbackExternal),
			_newMessageReadCallback(newMessageReadCallback),
			_port(port)
		{
		}

		~Server()
		{
			_networkThread.join();
		}

		/*
		 * Start the server.
		 */
		void run()
		{
			try {
				auto newConnectionCallbackInternal = std::bind(&Server::newConnectionCallbackInternal, this, std::placeholders::_1);

				asio::io_service ioService;

				tcp::endpoint endpoint(tcp::v4(), _port);
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

		/*
		 * Send a message to a specific client
		 * Parameters:
		 *	- uuid: The client's Id the message is to be sent to
		 *	- obj: The object to send. Must be serializable through the IJsonSerializable interface.
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
			sole::uuid uuid = sole::uuid0();
			std::string id = uuid.str();

			_clients.insert(std::make_pair(id, session));

			session->setId(id);

			_newConnectionCallbackExternal(id);
		}
	};

}
