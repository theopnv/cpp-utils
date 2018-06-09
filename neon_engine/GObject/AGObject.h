//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#pragma once

#include "IGObject.h"
#include "Vector.h"

namespace neon_engine
{

	/**
	 * \brief Abstract class for GameObject
	 */
	class AGObject : public IGObject
	{

	public:
		AGObject(const Vector2<int>& pos, const bool isEnabled = true) :
			_pos(pos),
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

		/**
		 * \brief Getter for the position
		 * \return Position of the game object
		 */
		Vector2<int>	getPos() const
		{
			return _pos;
		}

		/**
		 * \brief Setter for the position
		 * \param pos New position of the game object
		 */
		void			setPos(const Vector2<int> pos)
		{
			_pos = pos;
		}

	protected:
		Vector2<int>	_pos;
		bool			_isEnabled;
	};

}