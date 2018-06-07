//  Created by Theo Penavaire on 06/03/2018
//  Last Update on 06/07/2018 

#pragma once

#include "neon_engine.h"
#include "SDL.h"
#include "Core.h"

namespace neon_engine
{

	/**
	 * \brief Base class for every object managed by the graphical library (SDL2)
	 */
	class IGObject
	{

	public:
		virtual			~IGObject() = default;

		virtual bool	handleEvent(Sptr<SDL_Event> event) = 0;
		virtual void	draw(RendererSptr& renderer) = 0;

	};

}