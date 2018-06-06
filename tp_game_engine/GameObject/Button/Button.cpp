#include "Button.h"

namespace tp_game_engine
{

	Button::Button(TextureSptr texture, Vector4<int>& coord, bool isEnabled) :
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

			SDL_RenderCopy(renderer.get(), _texture.get(), NULL, &dest);
		}
	}

	bool Button::handleEvent(Sptr<SDL_Event> event)
	{
		return true;
	}

}