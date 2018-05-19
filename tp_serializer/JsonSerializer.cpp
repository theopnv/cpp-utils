#include "JsonSerializer.h"
#include <sstream>
#include <iostream>

namespace tp_serializer
{

	bool JsonSerializer::serialize(Sptr<IJsonSerializable> obj, std::string& output)
	{
		if (!obj) {
			return false;
		}

		Json::Value serializeRoot;
		obj->serialize(serializeRoot);

		std::ostringstream os;
		os << serializeRoot;
		output = os.str();

		return true;
	}

	bool JsonSerializer::deserialize(Sptr<IJsonSerializable> obj, std::string& input)
	{
		if (!obj) {
			return false;
		}

		Json::Value 		deserializeRoot;


		std::istringstream sin(input);
		sin >> deserializeRoot;

		obj->deserialize(deserializeRoot);
		return true;
	}
}