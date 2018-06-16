//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/08/2018 

#include "Core.h"
#include "SDL_image.h"

namespace neon_engine
{

	Core::Core(
		const std::string& winTitle,
		const Vector2<int> winSize,
		const Vector2<int> logicalWinSize) :
		_title(winTitle),
		_winSize(winSize),
		_logicalWinSize(logicalWinSize),
		_popState(false)
	{
	}

	Core::~Core()
	{
		if (_isInitialized) {
			SDL_Quit();
			TTF_Quit();
			IMG_Quit();
			SDL_StopTextInput();
		}
	}

	bool Core::start()
	{
		// General
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			throw NeonException("Initialization error");
		}
		_isInitialized = true;

		// Window
		_mainWindow = WindowSptr(SDL_CreateWindow(
			_title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_winSize.w(),
			_winSize.h(),
			SDL_WINDOW_SHOWN));
		if (!_mainWindow) {
			throw NeonException(SDL_GetError());
			return false;
		}
		SDL_StartTextInput();

		// Renderer
		_renderer = RendererSptr(SDL_CreateRenderer(
			_mainWindow.get(),
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
		SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
		if (!_renderer) {
			throw NeonException(SDL_GetError());
		}

		if (SDL_RenderSetLogicalSize(
			_renderer.get(),
			_logicalWinSize.w(),
			_logicalWinSize.h()) != 0)
		{
			throw NeonException(SDL_GetError());
		}
		
		// SDL_ttf
		if (TTF_Init() < 0) {
			throw NeonException("Can't initialize TTF_Font");
		}

		// SDL_Image
		const auto flags = IMG_INIT_JPG | IMG_INIT_PNG;
		const auto initted = IMG_Init(flags);

		if ((initted & flags) != flags) {
			throw NeonException("Can't initialize SDL_Image");
		}

		return true;
	}

	void Core::setEventFuncMapper(NEventFuncMapper& evFm)
	{
		buildEventMapper();
		_eventFuncMapper = evFm;
	}

}
