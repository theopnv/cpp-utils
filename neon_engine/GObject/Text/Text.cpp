//  Created by Theo Penavaire on 06/09/2018
//  Last Update on 06/09/2018 

#include "Text.h"

namespace neon_engine
{

	Text::Text(const RendererSptr& renderer,
		const std::string& font,
		const int fontSize,
		const Color fontColor,
		const std::string& text,
		const Alignement align,
		const Vector2<int> pos,
		const bool isEnabled) :
			AGObject(pos, isEnabled),
			_alignement(align)
	{
		_fontInfo = FontBuilder::fontToTexture(
			renderer,
			font,
			fontSize,
			fontColor,
			text);
	}
	
	void Text::draw(RendererSptr& renderer)
	{
		if (_isEnabled) {
			SDL_Rect	dest = {
				_pos.x(),
				_pos.y(),
				_fontInfo.size.w(),
				_fontInfo.size.h()
			};
			SDL_RenderCopy(renderer.get(), _fontInfo.texture.get(), nullptr, &dest);
		}
	}

	bool Text::update(NEvent& event)
	{
		return true;
	}

	Vector2<int> Text::getSize() const
	{
		return {_fontInfo.size.w(), _fontInfo.size.h() };
	}

	Text::Alignement Text::getAlignement() const
	{
		return _alignement;
	}
}
