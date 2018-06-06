#include "GEngine.h"

namespace tp_game_engine
{

	// geevent_mapper_builder
	namespace gmb
	{
		std::tuple<SDL_EventType, SDL_Keycode> getTuple(SDL_EventType et, SDL_Keycode k)
		{
			return std::make_tuple(et, k);
		}

		std::pair<GEEventType, GEEvent>	getPair(SDL_EventType et, SDL_Keycode k, GEEvent e)
		{
			return std::make_pair(getTuple(et, k), e);
		}
	}

	void GEngine::buildEventMapper()
	{
		_eventMapper.emplace(gmb::getPair(
			SDL_EventType::SDL_QUIT, SDLK_ESCAPE, GEEvent::esc));
	}

	void GEngine::handleEvents()
	{
		if (!_states.empty()) {

			try {
				SDL_Event event;

				if (SDL_PollEvent(&event)) {
					GEEvent	geevent = undefined;
					
					for (auto& evMap : _eventMapper) {
						auto[eventType, keycode] = evMap.first;

						if (event.type == eventType) {
							_eventFuncMapper.at(evMap.second)();
							return;
						}

						if (event.type == SDL_KEYDOWN
							&& event.key.keysym.sym == keycode) {
							_eventFuncMapper.at(evMap.second)();
							return;
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
	}

}