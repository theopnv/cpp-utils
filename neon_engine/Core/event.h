//  Created by Theo Penavaire on 06/03/2018
//  Last Update on 06/07/2018 

#pragma once

#include <functional>
#include <map>

namespace neon_engine
{

	/**
	 * \brief Event enumeration to interface from
	 * low level OS events (keyboard, mouse...) to game logic.
	 */
	enum NEvent
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
	};

	/**
	 * \brief Mapper of callbacks to fire when an event occured
	 * The user must provide its callbacks
	 * For example when NEvent::esc occured, onEscape() can be called
	 */
	using NEventFuncMapper = std::map<NEvent, std::function<void ()>>;
	
}