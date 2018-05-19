#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <string>
#include "MessageException.h"

namespace tp_network
{

	/*
	 * Structure:
	 *
	 *   +------------+-----------+ +----------------+
	 *   |	  Type    |	  Size    | |	   Data		 |
	 *   |	 header	  |	 header	  | |		    	 |
	 *   |    (4)     |    (4)    | |      (x)       |
	 *   +------------+-----------+ +----------------+
	 *
	 *  - Type header:
	 *  	- undefined: shouldn't appear. Error if so.
	 *  	- header: The message is the first one of the packet. It contains info
	 *  			  like packet size. (packet = group of messages)
	 *  	- content: Messages following the header
	 *  - Size header:
	 *  	Size of the data carried by the message
	 *  - Data:
	 *  	- If the message is a header, it's the number of messages forming a packet
	 *  	- If the message is content, it's data.
	 */
	class Message
	{

	  public:
		enum MsgType
		{
			undefined = 0,
			header = 1,
			content = 2,
		};

		enum
		{
			header_part_length = 4,
			header_length = 8,
		};
		enum
		{
			max_body_length = 4, // Do not exceed 9999
		};

		Message() {}

		Message(int expectedMsgCount)
		{
			setTypeHeaderInfo(MsgType::header);
			// +1 because this message counts too (the header one)
			init(std::to_string(expectedMsgCount + 1));
		}

		Message(const std::string& str)
		{
			setTypeHeaderInfo(MsgType::content);
			init(str + "\0");
		}

		void init(const std::string& str)
		{
			auto tmp = str;
			tmp += "\0";
			setSizeHeaderInfo(tmp.length() + TRAILING_ZERO);
			std::memcpy(getBody(), tmp.c_str(), getSizeHeaderInfo());
			encodeHeader();
		}

		char *getData()
		{
			return _data;
		}

		char *getBody()
		{
			return _data + header_length;
		}

		std::size_t getSizeHeaderInfo() const
		{
			return _sizeHeaderInfo;
		}

		void setSizeHeaderInfo(std::size_t new_length)
		{
			_sizeHeaderInfo = new_length;
			if (_sizeHeaderInfo > max_body_length + TRAILING_ZERO)
				_sizeHeaderInfo = max_body_length + TRAILING_ZERO;
		}

		MsgType getTypeHeaderInfo() const
		{
			return _typeHeaderInfo;
		}

		void setTypeHeaderInfo(MsgType msgType)
		{
			_typeHeaderInfo = msgType;
		}

		bool decodeHeader()
		{
			char type[header_part_length + TRAILING_ZERO] = "";
			std::strncat(type, _data, header_part_length);
			_typeHeaderInfo = (MsgType)std::atoi(type);

			char size[header_part_length + TRAILING_ZERO] = "";
			std::strncat(size, _data + header_part_length, header_part_length);
			_sizeHeaderInfo = std::atoi(size);
			if (_sizeHeaderInfo > max_body_length + TRAILING_ZERO)
			{
				_sizeHeaderInfo = 0;
				return false;
			}
			return true;
		}

		void encodeHeader()
		{
			if (_typeHeaderInfo == MsgType::undefined || _sizeHeaderInfo == 0) {
				throw InvalidFormatException();
			}

			char type[header_part_length + TRAILING_ZERO] = "";
			std::sprintf(type, "%4d", static_cast<int>(_typeHeaderInfo));
			std::memcpy(_data, type, header_part_length);

			char size[header_part_length + TRAILING_ZERO] = "";
			std::sprintf(size, "%4d", static_cast<int>(_sizeHeaderInfo));
			std::memcpy(_data + header_part_length, size, header_part_length);
		}

	  private:
		static const int 	TRAILING_ZERO = 1;

		MsgType				_typeHeaderInfo;
		int			 		_sizeHeaderInfo;
		char 				_data[header_length + max_body_length + 1];

	};

	using MessageQueue = std::deque<Message>;

};