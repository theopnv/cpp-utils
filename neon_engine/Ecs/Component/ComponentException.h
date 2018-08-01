#pragma once
#include <exception>
#include <string>

namespace neon_engine::ecs
{
	
	class ComponentNotFoundException : public std::exception
	{
		
	private:
		std::string		_message;

	public:
		explicit ComponentNotFoundException(const std::string& e) throw() : _message(e) {}
		ComponentNotFoundException() noexcept : _message("Component not found") {}

		virtual			~ComponentNotFoundException() noexcept = default;
		const char		*what() const noexcept override { return _message.c_str(); }

	};

}
