#pragma once

#include "json/json.h"

namespace tp_serializer
{

	/*
	* Base class for every serializable object.
	*/
	class IJsonSerializable
	{

	  public:
		virtual ~IJsonSerializable() = default;

		virtual void serialize(Json::Value& root) const = 0;
		virtual void deserialize(Json::Value& root) = 0;

	};

}