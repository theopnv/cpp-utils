#pragma once

#include <exception>
#include <string>

namespace neon_engine
{

	/**
	 * \brief Exception thrown by the NeonEngine
	 */
	class NeonException : public std::exception
	{
	  private:
		std::string			_message;

	  public:
		explicit NeonException(const std::string& e) throw() : _message(e) {}
		NeonException() throw() : _message("Neon Engine error") {}

		virtual				~NeonException() throw() = default;
		const char	*what() const throw() override { return _message.c_str(); }
	};

}