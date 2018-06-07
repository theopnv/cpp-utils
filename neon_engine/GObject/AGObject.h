//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#pragma once

#include "IGObject.h"

namespace neon_engine
{

	/**
	 * \brief Abstract class for GameObject
	 */
	class AGObject : public IGObject
	{

	public:
		AGObject(const bool isEnabled = true) :
			_isEnabled(isEnabled)
		{}
		virtual ~AGObject() = default;

		/**
		 * \brief Enable rendering and interaction for the game object
		 * \param e boolean
		 */
		void			setIsEnabled(const bool e)
		{
			_isEnabled = e;
		}

	protected:
		bool			_isEnabled;
	};

}