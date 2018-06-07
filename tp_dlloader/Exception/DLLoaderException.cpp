//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#include "DLLoaderException.h"

namespace exception
{

	DLLoaderException::DLLoaderException(const std::string &e) throw() :
		_message(e) {}

	const char *
	DLLoaderException::what() const throw()
	{
		return (_message.data());
	}
}