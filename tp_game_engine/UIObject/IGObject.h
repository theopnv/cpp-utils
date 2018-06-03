#pragma once

#include "tp_game_engine.h"
#include "SDL.h"
#include "GEngine.h"

namespace tp_game_engine
{

	/*
	* Base class for every object managed by the graphical library (SDL2)
	*/
	class IGObject
	{

	public:
		virtual			~IGObject() = default;

		virtual bool	handleEvent(Sptr<SDL_Event> event) = 0;
		virtual void	draw(Sptr<GEngine> ge) = 0;

	};

}