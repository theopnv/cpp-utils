#include "Image.h"

namespace tp_game_engine
{

	Image::Image(RendererSptr& renderer, 
		const std::string& file, 
		Vector4<int>& coord, 
		bool isEnabled) :
			AGObject(isEnabled),
			_coord(coord)
	{
		SDL_Surface	*surface;
		if (!(surface = IMG_Load(file.c_str()))) {
			throw GEngineException("Can't create a texture for image: " + file + ". " + SDL_GetError());
		} else {
			_coord.size.w(surface->w);
			_coord.size.h(surface->h);
			_texture = TextureSptr(SDL_CreateTextureFromSurface(renderer.get(), surface));
			if (!_texture) {
				throw GEngineException("Can't create a texture for image: " + file + ". " + SDL_GetError());
			}
		}
	}

	void Image::draw(RendererSptr& renderer)
	{
		if (_isEnabled) {
			SDL_Rect	dest = {
				_coord.pos.x(), 
				_coord.pos.y(), 
				_coord.size.w(), 
				_coord.size.h()
			};

			SDL_RenderCopy(renderer.get(), _texture.get(), NULL, &dest);
		}
	}

	bool Image::handleEvent(Sptr<SDL_Event> event)
	{
		return true;
	}

}