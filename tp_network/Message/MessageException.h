#pragma once

#include <exception>
#include <string>

namespace tp_network
{

	class InvalidFormatException : public std::exception
	{
	  private:
		std::string			_message;

	  public:
		InvalidFormatException(const std::string& e) throw() : _message(e) {}
		InvalidFormatException() throw() : _message("Invalid parameters were supplied") {}

		virtual				~InvalidFormatException() throw() = default;
		virtual const char	*what() const throw() { return _message.c_str(); }
	};

}