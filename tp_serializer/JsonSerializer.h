#pragma once

#include "IJsonSerializable.h"
#include <memory>

namespace tp_serializer
{

	template <class T>
	using Sptr = std::shared_ptr<T>;

	/*
	* Static class for serialization/deserialization of an object 
	* so that it doesn't need to be instantiated.
	*/
	class JsonSerializer
	{

	  public:
		static bool serialize(Sptr<IJsonSerializable> obj, std::string& output);
		static bool deserialize(Sptr<IJsonSerializable> obj, std::string& input);

	  private:
		JsonSerializer() = default;

	};

}