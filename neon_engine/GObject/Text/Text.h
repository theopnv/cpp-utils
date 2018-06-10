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
		 * \param coord Coordinates of the text
		 * \param isEnabled Active the game object
		 */
		Text(const RendererSptr& renderer,
			const std::string& font,
			int fontSize,
			Color fontColor,
			const std::string& text,
			Alignement align,
			const Vector4<int>& coord = { 0, 0, 0, 0 },
			bool isEnabled = true);
		~Text() = default;

		void	draw(RendererSptr& renderer) override;
		void	update(NEvent& event) override;

		/**
		 * \brief Getter for the alignement.
		 * Can be useful if the text is to be included in another game object
		 * and this game object needs to adapt its behaviour relatively to the text.
		 * \return Alignement of the button
		 */
		Alignement		getAlignement() const;

	private:
		Alignement		_alignement;
		TextureSptr		_texture;
	};

}
