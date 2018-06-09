//  Created by Theo Penavaire on 06/03/2018
//  Last Update on 06/07/2018 

#pragma once

#include "neon_engine.h"
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

		/**
		 * \brief Handle every event related to the game object
		 * \return true if operation succeeded 
		 */
		virtual bool	handleEvent() = 0;
		
		/**
		 * \brief Draw the game object on screen
		 * \param renderer Renderer's instance
		 */
		virtual void	draw(RendererSptr& renderer) = 0;

	};

}