//  Created by Theo Penavaire on 05/29/2018
//  Last Update on 06/08/2018 

#pragma once

#include "SdlPointer.h"
#include "Color.h"
#include "SDL_ttf.h"
#include "NeonException.h"
#include "Vector.h"
#include "SDL.h"

namespace neon_engine
{
	
	/**
	 * \brief Information about font
	 */
	struct FontInfo
	{
		/**
		 * \brief Width and Height of the font texture
		 */
		Vector2<int>	size;

		/**
		 * \brief Texture of the font
		 */
		TextureSptr		texture;

		FontInfo() = default;
		~FontInfo() = default;
		FontInfo(const Vector2<int> size_, TextureSptr texture_) :
			size(size_),
			texture(texture_)
		{}
	};

	/**
	 * \brief Load a TTF font and transform it into a SDL2 texture
	 */
	class FontBuilder
	{

	public:
		FontBuilder() = default;
		~FontBuilder() = default;

		static FontInfo		fontToTexture(
			RendererSptr renderer,
			const std::string& font,
			const int size,
			const Color color,
			const std::string& text)
		{
			TTF_Font	*font_ = TTF_OpenFont(font.c_str(), size);
			if (!font_) {
				throw NeonException("Can' load the following font: " + font);
			}

			const auto colorLevel = GameColors.at(color);
			SDL_Color	color_ = { colorLevel.r, colorLevel.g, colorLevel.b, colorLevel.a };
			SDL_Surface	*surface = TTF_RenderText_Solid(font_, text.c_str(), color_);
			if (!surface) {
				throw NeonException("Can' create a sprite for font: " + font + ". " + TTF_GetError());
			}

			TextureSptr texture = TextureSptr(SDL_CreateTextureFromSurface(renderer.get(), surface));
			if (!texture) {
				throw NeonException("Can't create a sprite for font: " + font + ". " + TTF_GetError());
			}
			
			auto fontInfo = FontInfo(Vector2<int>({ surface->w, surface->h }), texture);
			
			SDL_FreeSurface(surface);
			TTF_CloseFont(font_);

			return fontInfo;
		}

	};

}
