#pragma once

#include "SDL.h"

namespace tp_game_engine
{

	/*
	* Wrapper to use smart pointers with C-like SDL pointers.
	*/
	struct SDL_Deleter {
		void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); }
		void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
	};

	template<class T, class D = std::default_delete<T>>
	struct shared_ptr_with_deleter : public std::shared_ptr<T>
	{
		explicit shared_ptr_with_deleter(T* t = nullptr) :
			std::shared_ptr<T>(t, D())
		{}

		void reset(T* t = nullptr) {
			std::shared_ptr<T>::reset(t, D());
		}

	};

	using SurfacePtr = shared_ptr_with_deleter<SDL_Surface, SDL_Deleter>;
	using TextureSptr = shared_ptr_with_deleter<SDL_Texture, SDL_Deleter>;
	using RendererSptr = shared_ptr_with_deleter<SDL_Renderer, SDL_Deleter>;
	using WindowSptr = shared_ptr_with_deleter<SDL_Window, SDL_Deleter>;
}