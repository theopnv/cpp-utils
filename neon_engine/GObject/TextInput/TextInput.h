//  Created by Theo Penavaire on 06/10/2018
//  Last Update on 06/10/2018 

#include "AGObject.h"
#include "Image.h"

namespace neon_engine
{
	
	class TextInput : public AGObject
	{
		
	public:
		TextInput() = default;
		TextInput(Image& focusBg, 
			Image& noFocusBg, 
			Vector4<int>& coord, 
			bool isEnabled = true);
		~TextInput() = default;

		void	update(NEvent& event) override;
		void	draw(RendererSptr& renderer) override;

		/**
		 * \brief Getter for input associated with this control
		 * \return User input, or empty string if nothing was filled.
		 */
		std::string		getInput() const;

	private:
		std::string		_input;

		Image			_currentBg;
		Image			_focusBg;
		Image			_noFocusBg;
	};

}
