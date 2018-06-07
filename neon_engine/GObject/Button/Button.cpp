//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#include "Button.h"

namespace neon_engine
{

	Button::Button(const TextureSptr& texture, Vector4<int>& coord, const bool isEnabled) :
		AGObject(isEnabled),
		_texture(texture),
		_coord(coord)
	{

	}

	void Button::draw(RendererSptr& renderer)
	{
		if (_isEnabled) {
			SDL_Rect	dest = { 
				_coord.pos.x(), 
				_coord.pos.y(), 
				_coord.size.w(), 
				_coord.size.h()
			};

			SDL_RenderCopy(renderer.get(), _texture.get(), nullptr, &dest);
		}
	}

	bool Button::handleEvent(Sptr<SDL_Event> event)
	{
		return true;
	}

}