#pragma once

#include <exception>
#include <string>

namespace exception
{

	class DLLoaderException : public std::exception
	{
	  private:
		std::string	_message;

	  public:
		DLLoaderException(const std::string &e) throw();
		DLLoaderException() throw() = default;
		virtual		~DLLoaderException() throw() = default;


		const char *what() const throw();
	};

}
