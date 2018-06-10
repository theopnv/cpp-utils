//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#include "Button.h"

namespace neon_engine
{

	Button::Button(
		const Text& text, 
		const Vector4<int>& coord, 
		Event<void ()> onClick, 
		const bool isEnabled) :
		AGObject(coord, isEnabled),
		_onClick(onClick),
		_text(text)
	{
		setSize(text.getSize());
		_text.setPos(getPos());
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

			_text.draw(renderer);
		}
	}

	void Button::update(NEvent& event)
	{
		if (event.pos.x() > _coord.pos.x() 
			&& event.pos.x() < _coord.pos.x() + _coord.size.w()
			&& event.pos.y() > _coord.pos.y() 
			&& event.pos.y() < _coord.pos.y() + _coord.size.h()){
			_onClick();
		}
	}

}
