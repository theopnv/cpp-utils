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
			Vector4<int>& coord, 
			bool isEnabled = true);
		~Image() = default;

		bool	update(NEvent& event) override;
		void	draw(RendererSptr& renderer) override;

	private:
		TextureSptr					_texture;
		Vector2<int>				_size;
	};

}
