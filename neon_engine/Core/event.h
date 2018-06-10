//  Created by Theo Penavaire on 06/03/2018
//  Last Update on 06/07/2018 

#pragma once

#include <functional>
#include <map>
#include "Vector.h"

namespace neon_engine
{

	/**
	 * \brief Event enumeration to interface from
	 * low level OS events (keyboard, mouse...) to game logic.
	 */
	enum NEventType
	{
		undefined			= 0x00,
		
		up					= 0x10,
		down				= 0x11,
		left				= 0x12,
		right				= 0x13,
		esc					= 0x14,
		tab					= 0x15,
		enter				= 0x16,
		space				= 0x17,

		mouse_click			= 0x20,
	};

	/**
	 * \brief Event structure representing low level OS events
	 */
	struct NEvent
	{
		/**
		 * \brief Type of event
		 */
		NEventType		type;

		/**
		 * \brief Coordinates of event if relevant (e.g. mouse click)
		 * { -1, -1} if it is not relevant.
		 */
		Vector2<int>	pos;

		~NEvent() = default;
		explicit NEvent(NEventType t = undefined, 
			Vector2<int> p = Vector2<int>({-1, -1})) : 
			type(t), pos(p)
		{}
	};

	/**
	 * \brief Mapper of callbacks to fire when an event occured
	 * The user must provide its callbacks
	 * For example when NEvent::esc occured, onEscape() can be called
	 */
	using NEventFuncMapper = std::map<NEventType, std::function<void (NEvent&)>>;
	
}
