#pragma once

#include <functional>
#include <map>
#include <tuple>

namespace tp_game_engine
{

	enum GEEvent
	{
		undefined,
		up,
		down,
		left,
		right,
		esc,
		tab,
		enter,
		space,
	};

	using GEEventFuncMapper = std::map<GEEvent, std::function<void ()>>;

	using GEEventType = std::tuple<SDL_EventType, SDL_Keycode>;
	using GEEventMapper = std::map<GEEventType, GEEvent>;

}