//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#pragma once

#include "AGObject.h"
#include "Text.h"

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
		Button(const Text& text, const Vector2<int>& pos, bool isEnabled = true);
		~Button() = default;

		bool	handleEvent() override;
		void	draw(RendererSptr& renderer) override;

	private:
		Event<void(Sptr<AGObject>)>	_onClick;

		Text						_text;
		Vector2<int>				_size;
	};

}
