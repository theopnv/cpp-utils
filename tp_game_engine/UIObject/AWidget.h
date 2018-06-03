#pragma once

#include "IGObject.h"
#include "Vector.h"
#include "SdlPointer.h"

namespace tp_game_engine
{

	class AWidget : public IGObject
	{

	public:
		AWidget(TextureSptr texture, Vector2<int>& pos, bool isEnabled = true) :
			_texture(texture),
			_pos(pos),
			_isEnabled(isEnabled)
		{}
		virtual ~AWidget() = default;

	protected:
		TextureSptr		_texture;
		Vector2<int>	_pos;
		bool			_isEnabled;
	};

}