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