//  Created by Theo Penavaire on 06/10/2018
//  Last Update on 06/10/2018 

#include "AGObject.h"
#include "Image.h"
#include "Text.h"

namespace neon_engine
{
	
	class TextInput : public AGObject
	{
		
	public:
		TextInput() = default;
		/**
		 * \brief Constructor
		 * \param renderer Instance of the renderer
		 * \param focusBg Background image to use when focus is on this control (select)
		 * \param noFocusBg Background image to use when focus is not on this control (deselect)
		 * \param font Font to use to display text
		 * \param textColor Color of the text
		 * \param coord Coordinates relative to logical screen
		 * \param isEnabled 
		 */
		TextInput(RendererSptr& renderer,
			Image& focusBg, 
			Image& noFocusBg,
			const std::string& font,
			Color textColor,
			Vector4<int>& coord, 
			bool isEnabled = true);
		~TextInput() = default;

		void	update(NEvent& event) override;
		void	draw(RendererSptr& renderer) override;

		/**
		 * \brief Getter for input associated with this control
		 * \return User input, or empty string if nothing was filled.
		 */
		std::string		getInput() const;

		/**
		 * \brief Set the text to render in this control
		 * \param input the text to render in this control
		 */
		void			setInput(const std::string& input);

	private:
		RendererSptr	_renderer;

		std::string		_input;
		std::string		_previousInput;

		Image			_currentBg;
		Image			_focusBg;
		Image			_noFocusBg;

		Text			_text;
		std::string		_font;
		Color			_textColor;
	};

}
