//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#pragma once

#include <memory>

namespace tp_dlloader
{

	/**
	 * \brief Interface for Dynamic Library Loading (DLLoader)
	 * API for Unix and Windows. Handling of open, close, validity-check.
	 * \tparam T Type of the class to load
	 */
	template <class T>
	class IDLLoader
	{

	public:

		virtual ~IDLLoader() = default;

		/**
		 * \brief Open the shared library and store it in an internal handler
		 */
		virtual void DLOpenLib() = 0;

		/**
		 * \brief Load the class in memory and point to it
		 * \return shared pointer to an instance of the class
		 */
		virtual std::shared_ptr<T>	DLGetInstance() = 0;

		/**
		 * \brief Correctly delete the instance of the "dynamically loaded" class.
		 */
		virtual void DLCloseLib() = 0;

	};
}