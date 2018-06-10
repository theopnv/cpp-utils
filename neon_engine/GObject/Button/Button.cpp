//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#include "Button.h"

namespace neon_engine
{

	Button::Button(const Text& text, const Vector2<int>& pos, Event<void ()> onClick, const bool isEnabled) :
		AGObject(pos, isEnabled),
		_text(text),
		_size(text.getSize()),
		_onClick(onClick)
	{
		if (text.getAlignement() == Text::Alignement::right)
		{
			const auto xOffset = _pos.x() - _size.w();
			_text.setPos({ xOffset, _pos.y() });
		}
		else
		{
			_text.setPos({ _pos.x(), _pos.y() });
		}

		_pos = _text.getPos();
	}

	void Button::draw(RendererSptr& renderer)
	{
		if (_isEnabled) {
			SDL_Rect	dest = { 
				_pos.x(), 
				_pos.y(), 
				_size.w(), 
				_size.h()
			};

			_text.draw(renderer);
		}
	}

	bool Button::update(NEvent& event)
	{
		if (event.pos.x() > _pos.x() && event.pos.x() < _pos.x() + _size.w()
			&& event.pos.y() > _pos.y() && event.pos.y() < _pos.y() + _size.y()){
			_onClick();
		}
		return true;
	}

}
