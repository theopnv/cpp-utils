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

		/**
		 * \brief Comparison of images based on file path, position and size.
		 * May not be ultra accurate, so see later if this can be optimized.
		 * \param other Image to compare 
		 * \return true if images are the same
		 */
		bool operator==(const Image& other) const;

		void	update(NEvent& event) override;
		void	draw(RendererSptr& renderer) override;

	private:
		TextureSptr		_texture;

		std::string		_file;
	};

}
