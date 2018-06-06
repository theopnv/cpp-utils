#pragma once

#include "IGObject.h"
#include "Vector.h"
#include "SdlPointer.h"

namespace tp_game_engine
{

	class AGObject : public IGObject
	{

	public:
		AGObject(bool isEnabled = true) :
			_isEnabled(isEnabled)
		{}
		virtual ~AGObject() = default;

		void			setIsEnabled(bool e)
		{
			_isEnabled = e;
		}

	protected:
		bool			_isEnabled;
	};

}