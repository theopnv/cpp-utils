//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include <string>

namespace tp_network
{

		/**
		* \brief Packet related data for server and client classes.
		* Useful to assemble/disassemble packets to/into messages queues.
		*/
		struct PacketBuild
		{
			int 			_expectedMsgCount;
			std::string		_data;
			int 			_currentMsgIdx;

			explicit PacketBuild(const int expectedMsgCount) :
				_expectedMsgCount(expectedMsgCount),
				_data(""),
				_currentMsgIdx(0)
			{}

			PacketBuild() :
				_expectedMsgCount(0),
				_data(""),
				_currentMsgIdx(0)
			{}
		};

}