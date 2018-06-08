//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include "IJsonSerializable.h"
#include <memory>
#include <string>

namespace tp_serializer
{

	template <class T>
	using Sptr = std::shared_ptr<T>;

	/**
	* \brief Static class for serialization/deserialization of an object 
	* so that it doesn't need to be instantiated.
	*/
	class JsonSerializer
	{

	  public:
		/**
		 * \brief Stringify a serializable object
		 * \param obj Object to serialize
		 * \param output Result string (reference)
		 * \return true if operation succeeded
		 */
		static bool serialize(const Sptr<IJsonSerializable>& obj, std::string& output);

		/**
		 * \brief Deserialize a serializable object from a string
		 * \param obj Deserialized object
		 * \param input Stringified object
		 * \return true if operation succeeded
		 */
		static bool deserialize(const Sptr<IJsonSerializable>& obj, std::string& input);

	  private:
		JsonSerializer() = default;

	};

}
