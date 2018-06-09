//  Created by Theo Penavaire on 06/06/2018
//  Last Update on 06/07/2018 

#include "Image.h"
#include "SDL_image.h"

namespace neon_engine
{

	Image::Image(RendererSptr& renderer, 
		const std::string& file, 
		Vector4<int>& coord, 
		bool isEnabled) :
			AGObject(coord.pos, isEnabled),
			_size(coord.size)
	{
		SDL_Surface	*surface;
		if (!(surface = IMG_Load(file.c_str()))) {
			throw NeonException("Can't create a texture for image: " + file + ". " + SDL_GetError());
		} else {
			_size.w(surface->w);
			_size.h(surface->h);
			_texture = TextureSptr(SDL_CreateTextureFromSurface(renderer.get(), surface));
			if (!_texture) {
				throw NeonException("Can't create a texture for image: " + file + ". " + SDL_GetError());
			}
		}
	}

	void Image::draw(RendererSptr& renderer)
	{
		if (_isEnabled) {
			SDL_Rect	dest = {
				_pos.x(), 
				_pos.y(), 
				_size.w(), 
				_size.h()
			};

			SDL_RenderCopy(renderer.get(), _texture.get(), nullptr, &dest);
		}
	}

	bool Image::handleEvent()
	{
		return true;
	}

}
