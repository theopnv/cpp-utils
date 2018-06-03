#include "GEngine.h"

namespace tp_game_engine
{
	
	bool GEngine::run()
	{
		while (!_stop) {

			if (SDL_RenderClear(_renderer.get()) < 0) {
				std::cerr << SDL_GetError() << std::endl;
			}

			handleEvents();
			update();
			draw();

			SDL_RenderPresent(_renderer.get());
			
		}

		cleanup();

		return true;
	}

}