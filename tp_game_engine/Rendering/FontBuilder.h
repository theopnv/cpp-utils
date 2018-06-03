#pragma once

#include "SdlPointer.h"
#include "Color.h"
#include "SDL_ttf.h"
#include "GEngineException.h"
#include "Vector.h"

namespace tp_game_engine
{
	
	struct FontInfo
	{
		Vector2<int>	size;
		TextureSptr		texture;

		FontInfo(Vector2<int> size_, TextureSptr texture_) :
			size(size_),
			texture(texture_)
		{}
	};

	class FontBuilder
	{

	public:
		FontBuilder() = default;
		~FontBuilder() = default;

		static FontInfo		fontToTexture(
			RendererSptr renderer,
			const std::string& font,
			int size,
			Color color,
			const std::string& text)
		{
			TTF_Font	*font_ = TTF_OpenFont(font.c_str(), size);
			if (!font_) {
				throw GEngineException("Can' load the following font: " + font);
			}
			
			ColorLevel	colorLevel = GameColors.at(color);
			SDL_Color	color_ = { colorLevel.r, colorLevel.g, colorLevel.b, colorLevel.a };
			SDL_Surface	*surface = TTF_RenderText_Solid(font_, text.c_str(), color_);
			if (!surface) {
				throw GEngineException("Can' create a sprite for font: " + font + ". " + TTF_GetError());
			}

			TextureSptr texture = TextureSptr(SDL_CreateTextureFromSurface(renderer.get(), surface));
			if (!texture) {
				throw GEngineException("Can't create a sprite for font: " + font + ". " + TTF_GetError());
			}
			
			auto fontInfo = FontInfo(Vector2<int>({ surface->w, surface->h }), texture);
			
			SDL_FreeSurface(surface);
			
			return fontInfo;
		}

	};

}
