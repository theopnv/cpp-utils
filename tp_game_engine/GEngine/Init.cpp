#include "GEngine.h"

namespace tp_game_engine
{

	GEngine::GEngine(
		const std::string& winTitle, 
		int width, 
		int height) :
		_title(winTitle),
		_width(width),
		_height(height)
	{
	}

	GEngine::~GEngine()
	{
		if (_isInitialized) {
			SDL_Quit();
			TTF_Quit();
		}
	}

	bool GEngine::start()
	{
		// General
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			throw GEngineException("Initialization error");
		}
		_isInitialized = true;

		// Window
		_mainWindow = WindowSptr(SDL_CreateWindow(
			_title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_width,
			_height,
			SDL_WINDOW_SHOWN));
		if (!_mainWindow) {
			throw GEngineException("Can't create the main window");
			return false;
		}

		// Renderer
		_renderer = RendererSptr(SDL_CreateRenderer(
			_mainWindow.get(),
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
		SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
		if (!_renderer) {
			throw GEngineException("Can't create the graphic renderer");
			return false;
		}
		
		// SDL_ttf
		if (TTF_Init() < 0) {
			throw GEngineException("Can't initialize TTF_Font");
			return false;
		}

		return true;
	}

	void GEngine::setEventFuncMapper(GEEventFuncMapper& evFM)
	{
		buildEventMapper();
		_eventFuncMapper = evFM;
	}

}