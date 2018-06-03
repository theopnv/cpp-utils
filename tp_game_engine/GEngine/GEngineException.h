#pragma once

#include <exception>
#include <string>

namespace tp_game_engine
{

	class GEngineException : public std::exception
	{
	  private:
		std::string			_message;

	  public:
		GEngineException(const std::string& e) throw() : _message(e) {}
		GEngineException() throw() : _message("A graphical error has occured") {}

		virtual				~GEngineException() throw() = default;
		virtual const char	*what() const throw() { return _message.c_str(); }
	};

}