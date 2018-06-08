//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include "json/json.h"

namespace tp_serializer
{

	/**
	 * \brief Base class for every serializable object.
	 */
	class IJsonSerializable
	{

	  public:
		virtual ~IJsonSerializable() = default;

		/**
		 * \brief Explain how to serialize the object. For more information look at the jsoncpp library documentation.
		 * \param root
		 */
		virtual void serialize(Json::Value& root) const = 0;

		/**
		 * \brief Explain how to deserialize the object. For more information look at the jsoncpp library documentation.
		 * \param root 
		 */
		virtual void deserialize(Json::Value& root) = 0;

	};

}