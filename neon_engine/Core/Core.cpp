//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/08/2018 

#include "Core.h"

namespace neon_engine
{
	
	void Core::run()
	{
		while (!_stop) {

			if (SDL_RenderClear(_renderer.get()) < 0) {
				std::cerr << SDL_GetError() << std::endl;
			}

			auto event = handleEvents();
			update(event);
			draw();

			SDL_RenderPresent(_renderer.get());
			
		}

		stop();
	}

	void Core::stop()
	{
		cleanupStates();
	}

}