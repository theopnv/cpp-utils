//  Created by Theo Penavaire on 06/04/2018
//  Last Update on 06/08/2018 

#include "Core.h"

namespace neon_engine
{

	std::tuple<SDL_EventType, SDL_Keycode> 
	Core::getTuple(SDL_EventType et, SDL_Keycode k)
	{
		return std::make_tuple(et, k);
	}

	std::pair<Core::NEventType, NEvent>
	Core::getPair(const SDL_EventType et, const SDL_Keycode k, NEvent e)
	{
		return std::make_pair(getTuple(et, k), e);
	}

	void Core::buildEventMapper()
	{
		_eventMapper.emplace(getPair(SDL_QUIT, SDLK_ESCAPE, NEvent(esc)));
		_eventMapper.emplace(getPair(SDL_MOUSEBUTTONDOWN, SDLK_UNKNOWN, NEvent(mouse_click)));
	}

	NEvent Core::handleEvents()
	{
		if (!_states.empty()) {

			try {
				SDL_Event event;

				if (SDL_PollEvent(&event)) {
					for (auto& evMap : _eventMapper) {
						auto[eventType, keycode] = evMap.first;

						if (event.type == eventType) {
							if (eventType == SDL_MOUSEBUTTONDOWN) {
								evMap.second.pos = { event.button.x, event.button.y };
							}
							try {
								_eventFuncMapper.at(evMap.second.type)(evMap.second);
							} catch (const std::out_of_range&){
								return evMap.second;
							}
						}

						if (event.type == SDL_KEYDOWN
							&& event.key.keysym.sym == keycode) {
							try {
								_eventFuncMapper.at(evMap.second.type)(evMap.second);
							} catch (const std::out_of_range&){
								return evMap.second;
							}
						}
					}
				}
			}
			catch (std::out_of_range& e) {
				std::cerr << "No callback was specified for this event" << std::endl;
			}
		}
		else {
			std::cerr << "Empty stack of states" << std::endl;
		}

		return NEvent();
	}

}