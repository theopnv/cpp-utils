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

			// Clean old states flagged for deletion
			if (_popState) {
				if (_states.size() >= 2) {
					const auto currentState = _states.top();
					_states.pop();

					_states.top()->cleanup();
					_states.pop();

					_states.push(currentState);
				}
				_popState = false;
			}
		}

		stop();
	}

	void Core::stop()
	{
		cleanupStates();
	}

}