#pragma once

#include <asio.hpp>
#include <iostream>
#include <functional>
#include "tp_network.h"
#include "Session.h"

namespace tp_network
{

	/*
	 * This class is used to set the listener & acceptor on the port.
	 * Don't use this class to handle your connections, always use
	 * the upper-level "Server" class (Server.h) !
	 * Must be provided with :
	 * 	- ioService
	 * 		--> See boost Asio documentation for further information
	 * 	- endpoint
	 * 		--> See boost Asio documentation for further information
	 * 	- connection callback
	 * 		--> Will be called when a new client got accepted
	 * 	- packet read callback
	 * 		--> Will be called when a packet is read on the socket
	 */
	class GenericServer
	{

	  public:
		GenericServer(asio::io_service& ioService,
					  const tcp::endpoint& endpoint,
					  Event<void (SessionSP)> newConnectionCallback,
					  Event<void (const std::string&, const std::string&)> newMessageReadCallback) :
			_ioService(ioService),
			_acceptor(ioService, endpoint),
			_socket(ioService),
			_newConnectionCallback(newConnectionCallback),
			_newMessageReadCallback(newMessageReadCallback)
		{
			doAccept();
		}

	  private:

		asio::io_service&			_ioService;
		tcp::acceptor				_acceptor;
		tcp::socket					_socket;
		Event<void (SessionSP)>		_newConnectionCallback;
		Event<void (const std::string&, const std::string&)>	_newMessageReadCallback;

		void doAccept()
		{
			_acceptor.async_accept(_socket,
								   [this](std::error_code ec)
								   {
									   if (!ec)
									   {
										   auto session = std::make_shared<Session>(
										   	std::move(_socket), _newMessageReadCallback);
										   _newConnectionCallback(session);
										   session->start();
									   }
									   doAccept();
								   });
		}

	};

}