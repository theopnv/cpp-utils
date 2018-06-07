//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#pragma once

#include "AGObject.h"
#include "Vector.h"

namespace neon_engine
{

	/**
	 * \brief Button class
	 * Triggers an event on click
	 */
	class Button : public AGObject
	{

	public: 
		Button() = default;
		Button(const TextureSptr& texture, Vector4<int>& pos, bool isEnabled = true);
		~Button() = default;

		bool	handleEvent(Sptr<SDL_Event> event) override;
		void	draw(RendererSptr& renderer) override;

	private:
		Event<void(Sptr<AGObject>)>	_onClick;

		TextureSptr					_texture;
		Vector4<int>				_coord;
	};

}
