//  Created by Theo Penavaire on 06/10/2018
//  Last Update on 06/10/2018 

#include "TextInput.h"

namespace neon_engine
{
	
	TextInput::TextInput(RendererSptr& renderer,
		Image& focusBg, 
		Image& noFocusBg,
		const std::string& font,
		Color textColor,
		Vector4<int>& coord, 
		bool isEnabled) :
		AGObject(coord, isEnabled),
		_renderer(renderer),
		_currentBg(noFocusBg),
		_focusBg(focusBg),
		_noFocusBg(noFocusBg),
		_font(font),
		_textColor(textColor)
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
		// Focus
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

		if (getHasFocus())
		{
			// Backspace
			if (event.type == backspace && !_input.empty()) {
				_input.pop_back();
			}

			// Text
			if (!event.text.empty()) {
				_input += event.text;
			}

			if (!_input.empty())
			{
				const auto textCoord = Vector4<int>(_coord.pos.x() + 10, _coord.pos.y() + 12);
				_text = Text(_renderer,
					_font,
					_coord.size.h(),
					_textColor,
					_input,
					Text::left,
					textCoord
				);
			}
		}
	}

	void	TextInput::draw(RendererSptr& renderer)
	{
		_currentBg.draw(renderer);
		if (!_input.empty())
		{
			_text.draw(renderer);
		}
	}

}