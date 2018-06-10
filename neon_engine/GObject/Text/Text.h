//  Created by Theo Penavaire on 06/09/2018
//  Last Update on 06/09/2018 

#pragma once

#include "AGObject.h"
#include "Color.h"
#include "FontBuilder.h"

namespace neon_engine
{

	/**
	 * \brief Utility to display text
	 */
	class Text : public AGObject
	{

	public:

		/**
		 * \brief Self explanatory
		 */
		enum Alignement
		{
			left,
			right,
			center,
		};

		Text() = default;

		/**
		 * \brief Constructor for Text
		 * \param renderer The renderer's instance
		 * \param font Font to use
		 * \param fontSize Size of the text (relative to the logical window size)
		 * \param fontColor Color of the text
		 * \param text Text to display
		 * \param align Alignement of the text
		 * \param pos Position of the text
		 * \param isEnabled Active the game object
		 */
		Text(const RendererSptr& renderer,
			const std::string& font,
			int fontSize,
			Color fontColor,
			const std::string& text,
			Alignement align,
			const Vector2<int> pos = { 0, 0 },
			bool isEnabled = true);
		~Text() = default;

		void	draw(RendererSptr& renderer) override;
		bool	update(NEvent& event) override;

		/**
		 * \brief Getter for the text's texture size.
		 * Can be useful if the text is to be included in another game object
		 * and this game object needs to adapt its size relatively to the text.
		 * \return Size of the texture of the text
		 */
		Vector2<int>	getSize() const;

		/**
		 * \brief Getter for the alignement.
		 * Can be useful if the text is to be included in another game object
		 * and this game object needs to adapt its behaviour relatively to the text.
		 * \return Alignement of the button
		 */
		Alignement		getAlignement() const;

	private:
		Alignement		_alignement;
		FontInfo		_fontInfo;
	};

}
