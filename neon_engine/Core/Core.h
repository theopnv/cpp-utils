//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/08/2018 

#pragma once

// C++
#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <tuple>

// SDL2
#include "SDL.h"
#include "SDL_ttf.h"

// neon_engine
#include "neon_engine.h"
#include "IGameState.h"
#include "SdlPointer.h"
#include "NeonException.h"
#include "event.h"
#include "Vector.h"

namespace neon_engine
{

	class IGameState;

	/**
	 * \brief Main class of the game engine
	 * Handles the pipeline :
	 *  1. Creation of window
	 *  2. GameLoop
	 *		A. Clear screen
	 *		B. Event management
	 *		C. Buffer update
	 *		D. Screen rendering
	 *	3. Exit
	 */
	class Core : public std::enable_shared_from_this<Core>
	{

	public:
		/**
		 * \brief 
		 * \param winTitle Title of the window
		 * \param winSize Real size of the window
		 * \param logicalWinSize Independant resolution for rendering
		 */
		Core(
			const std::string& winTitle,
			const Vector2<int> winSize,
			const Vector2<int> logicalWinSize);
		~Core();

		/**
		 * \brief Start the game engine
		 * \return true if operation succeeded
		 */
		bool start();

		/**
		 * \brief Game loop
		 */
		void run();

		/**
		 * \brief Stop the game engine
		 */
		void	stop();

		/**
		 * \brief Change the state
		 * \param state new state
		 */
		void	changeState(const Sptr<IGameState>& state);

		/**
		 * \brief Will pause the current state and change to a new one
		 * \param state new state
		 */
		void	pushState(const Sptr<IGameState>& state);
		
		/**
		 * \brief Will cleanup the current state, and resume the older one if present
		 */
		void	popState();
		
		// Event Manager
		void	setEventFuncMapper(NEventFuncMapper& evFm);
		
		bool				_stop = false;
		RendererSptr		_renderer;

	private:

		/**
		* \brief Low-level types of event (SDL2)
		*/
		using NEventType = std::tuple<SDL_EventType, SDL_Keycode>;

		/**
		* \brief Internal mapper between NEventType and higher event types NEvent
		*/
		using NEventMapper = std::map<NEventType, NEvent>;

		static std::tuple<SDL_EventType, SDL_Keycode> 
			getTuple(SDL_EventType et, SDL_Keycode k);
		static std::pair<NEventType, NEvent> 
			getPair(SDL_EventType et, SDL_Keycode k, NEvent e);

		bool				_isInitialized = false; /* Check if SDL was well initialized */

		// Main window parameters
		WindowSptr			_mainWindow;
		std::string			_title;
		Vector2<int>		_winSize;
		Vector2<int>		_logicalWinSize;

		std::stack<Sptr<IGameState>>	_states;
		NEventFuncMapper				_eventFuncMapper;
		NEventMapper					_eventMapper;

		/**
		* \brief Main event loop. Interface with low-level events (SDL2).
		*/
		void	handleEvents();

		/**
		* \brief Call the upper state and update it
		*/
		void	update();

		/**
		 * \brief Call the upper state and render it
		 */
		void	draw();

		/**
		 * \brief Build the low-level event mapper (to interact with SDL2 events).
		 */
		void	buildEventMapper();

		/*
		 * Call cleanup on all registered states.
		 */
		void	cleanupStates();
	};

}
