#include "Button.h"

namespace tp_game_engine
{

	Button::Button(TextureSptr texture, Vector4<int>& coord, bool isEnabled) :
		AWidget(texture, Vector2<int>(coord.pos), isEnabled),
		_size(coord.size)
	{

	}

	void Button::draw(RendererSptr& renderer)
	{
		SDL_Rect	dest = { _pos.x(), _pos.y(), _size.w(), _size.h() };
		SDL_RenderCopy(renderer.get(), _texture.get(), NULL, &dest);
	}

	bool Button::handleEvent(Sptr<SDL_Event> event)
	{
		return true;
	}

}