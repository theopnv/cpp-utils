//  Created by Theo Penavaire on 06/06/2018
//  Last Update on 06/07/2018 

#pragma once

#include "AGObject.h"
#include "Vector.h"

namespace neon_engine
{

	/**
	 * \brief Renders an image
	 */
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
