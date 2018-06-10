//  Created by Theo Penavaire on 06/10/2018
//  Last Update on 06/10/2018 

#include "TextInput.h"

namespace neon_engine
{
	
	TextInput::TextInput(Image& focusBg, 
		Image& noFocusBg, 
		Vector4<int>& coord, 
		bool isEnabled) :
		AGObject(coord, isEnabled),
		_currentBg(noFocusBg),
		_focusBg(focusBg),
		_noFocusBg(noFocusBg)
	{
		setSize(_currentBg.getSize());
		_currentBg.setPos(_coord.pos);
		_focusBg.setPos(_coord.pos);
		_noFocusBg.setPos(_coord.pos);
	}

	std::string	TextInput::getInput() const
	{
		return _input;
	}

	void	TextInput::update(NEvent& event)
	{
		if (event.type == NEventType::mouse_click)
		{
			if (event.pos.x() > _coord.pos.x() 
				&& event.pos.x() < _coord.pos.x() + _coord.size.w()
				&& event.pos.y() > _coord.pos.y() 
				&& event.pos.y() < _coord.pos.y() + _coord.size.h()) {
				setHasFocus(true);
				_currentBg = _focusBg;
			}
			else {
				setHasFocus(false);
				_currentBg = _noFocusBg;
			}
		}
		
		if (getHasFocus()) {
			_input += event.keyName;
		}
	}

	void	TextInput::draw(RendererSptr& renderer)
	{
		_currentBg.draw(renderer);
	}

}