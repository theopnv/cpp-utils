#pragma once

#include "AGObject.h"

namespace tp_game_engine
{

	class Button : public AGObject
	{

	public: 
		Button() = default;
		Button(TextureSptr texture, Vector4<int>& pos, bool isEnabled = true);
		~Button() = default;

		bool	handleEvent(Sptr<SDL_Event> event) override;
		void	draw(RendererSptr& renderer) override;

	private:
		Event<void(Sptr<AGObject>)>	_onClick;

		TextureSptr					_texture;
		Vector4<int>				_coord;
	};

}