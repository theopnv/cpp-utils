#pragma once

#include <string>

namespace tp_network
{

		/*
		* Packet related data for server and client classes.
		* Useful to assemble/disassemble packets to/into messages queues.
		*/
		struct PacketBuild
		{
			int 			_expectedMsgCount;
			std::string		_data;
			int 			_currentMsgIdx;

			PacketBuild(int expectedMsgCount) :
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