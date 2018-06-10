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
		const Vector4<int>& coord,
		const bool isEnabled) :
			AGObject(coord, isEnabled),
			_alignement(align)
	{
		auto fontInfo = FontBuilder::fontToTexture(
			renderer,
			font,
			fontSize,
			fontColor,
			text);

		setSize(fontInfo.size);
		_texture = fontInfo.texture;

		if (getAlignement() == Text::Alignement::right)
		{
			const auto xOffset = _coord.pos.x() - _coord.size.w();
			setPos({ xOffset, _coord.pos.y() });
		}
		else
		{
			setPos({ _coord.pos.x(), _coord.pos.y() });
		}
	}
	
	void Text::draw(RendererSptr& renderer)
	{
		if (_isEnabled) {
			SDL_Rect	dest = {
				_coord.pos.x(),
				_coord.pos.y(),
				_coord.size.w(),
				_coord.size.h()
			};
			SDL_RenderCopy(renderer.get(), _texture.get(), nullptr, &dest);
		}
	}

	void Text::update(NEvent& event)
	{
	}

	Text::Alignement Text::getAlignement() const
	{
		return _alignement;
	}
}
