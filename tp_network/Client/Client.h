#pragma once

#include <string>
#include <iostream>
#include <thread>
#include "asio.hpp"
#include "typedefs.h"
#include "GenericClient.h"

namespace tp_network
{

	/*
	* Client class
	* Should be started in a separated thread
	* Must be provided with :
	* 	- ip
	* 		--> The IP address the client must connect to
	*	- port
	*		--> The port the client must connect to
	*	- newPacketCallback
	*		--> Will be called when a new packet is received
	*/
	class Client
	{

	  public:

		Client(const std::string& ip,
			   unsigned short port,
			   Event<void (const std::string&)> newPacketReadCallback) :
			_ip(ip),
			_port(port),
			_newPacketReadCallback(newPacketReadCallback),
			_client(_ioService, newPacketReadCallback)
		{
		}

		/*
		* Start the client. Try to connect to ip:port.
		*/
		void run()
		{
			try {
				tcp::resolver resolver(_ioService);
				auto endpointIterator = resolver.resolve(_ip, std::to_string(_port));

				_client.setEndpointIterator(endpointIterator);
				_client.start();

				_ioService.run();

			} catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}

		/*
		* Send a packet to server.
		*/
		bool send(std::string& packet)
		{
			return _client.write(packet);
		}

	  private:
		asio::io_service			_ioService;
		std::string				_ip;
		unsigned short			_port;
		Event<void (const std::string&)>	_newPacketReadCallback;
		GenericClient			_client;
	};


}