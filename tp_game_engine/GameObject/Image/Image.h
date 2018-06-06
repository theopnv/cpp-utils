#pragma once

#include "AGObject.h"
#include "SDL_image.h"

namespace tp_game_engine
{

	class Image : public AGObject
	{

	public: 
		Image() = default;
		Image(RendererSptr& renderer,
			const std::string& file, 
			Vector4<int>& pos, 
			bool isEnabled = true);
		~Image() = default;

		bool	handleEvent(Sptr<SDL_Event> event) override;
		void	draw(RendererSptr& renderer) override;

	private:
		TextureSptr					_texture;
		Vector4<int>				_coord;
	};

}