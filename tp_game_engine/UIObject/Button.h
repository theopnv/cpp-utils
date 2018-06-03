#pragma once

#include "AWidget.h"

namespace tp_game_engine
{

	class Button : public AWidget
	{

	public: 
		Button() = default;
		Button(TextureSptr texture, Vector4<int>& pos, bool isEnabled = true);
		~Button() = default;

		bool	handleEvent(Sptr<SDL_Event> event) override;
		void	draw(Sptr<GEngine> ge) override;

	private:
		Event<void(Sptr<AWidget>)>	_onClick;
		Vector2<int>				_size;
	};

}