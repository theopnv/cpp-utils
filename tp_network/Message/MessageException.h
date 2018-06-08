//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include <exception>
#include <string>

namespace tp_network
{

	/**
	 * \brief Exception thrown by tp_network classes
	 */
	class InvalidFormatException : public std::exception
	{
	  private:
		std::string			_message;

	  public:
		explicit InvalidFormatException(const std::string& e) throw() : _message(e) {}
		InvalidFormatException() throw() : _message("Invalid parameters were supplied") {}

		virtual				~InvalidFormatException() throw() = default;
		const char	*what() const throw() override { return _message.c_str(); }
	};

}