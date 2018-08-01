//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/07/2018 

#pragma once

#include "AUIObject.h"
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
		/**
		 * \brief Constructor for Button
		 * \param text Text to display
		 * \param coord Coordinates of the button
		 * \param onClick Callback to trigger when the button is clicked
		 * \param isEnabled Activation of the button
		 */
		Button(const Text& text, 
			const Vector4<int>& coord, 
			Event<void()> onClick, 
			bool isEnabled = true);
		~Button() = default;

		void	update(NEvent& event) override;
		void	draw(RendererSptr& renderer) override;

	private:
		Event<void()>	_onClick;

		Text			_text;
	};

}
