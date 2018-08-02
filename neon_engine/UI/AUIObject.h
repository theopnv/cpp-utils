//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#pragma once

#include "IUIObject.h"
#include "Vector.h"

namespace neon_engine
{

	/**
	 * \brief Abstract class for GameObject
	 */
	class AGObject : public IUIObject
	{

	public:
		AGObject() = default;
		explicit AGObject(const Vector4<int>& coord, const bool isEnabled = true) :
			_isEnabled(isEnabled),
			_hasFocus(false),
			_coord(coord)
		{}
		virtual ~AGObject() = default;

		void			setIsEnabled(const bool e) override
		{
			_isEnabled = e;
		}

		Vector2<int>	getPos() const override
		{
			return _coord.pos;
		}

		void			setPos(const Vector2<int> pos) override
		{
			_coord.pos = pos;
		}
		
		Vector2<int>	getSize() const override
		{
			return _coord.size;
		}

		void			setSize(const Vector2<int> size) override
		{
			_coord.size = size;
		}

		void			setHasFocus(const bool hasFocus) override
		{
			_hasFocus = hasFocus;
		}

		bool			getHasFocus() const override
		{
			return _hasFocus;
		}

	protected:
		bool			_isEnabled;
		bool			_hasFocus;

		Vector4<int>	_coord;
	};

}