#pragma once

// C++
#include <memory>
#include <string>
#include <iostream>
#include <string>
#include <stack>

// SDL2
#include "SDL.h"
#include "SDL_ttf.h"

// tp_game_engine
#include "tp_game_engine.h"
#include "IGameState.h"
#include "SdlPointer.h"
#include "GEngineException.h"

namespace tp_game_engine
{

	class AGameState;

	class GEngine : public std::enable_shared_from_this<GEngine>
	{

	public:
		GEngine(const std::string& winTitle, int width, int height);
		~GEngine();

		bool start();
		bool run();

		// State Manager
		void	cleanup();
		void	changeState(Sptr<IGameState> state);
		void	pushState(Sptr<IGameState> state);
		void	popState();
		void	handleEvents();
		void	update();
		void	draw();

		bool				_stop = false;
		RendererSptr		_renderer;

	private:

		bool				_isInitialized = false;

		// Main window parameters
		WindowSptr			_mainWindow;
		std::string			_title;
		int					_width;
		int					_height;

		std::stack<Sptr<IGameState>>	_states;
	};

}