//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/08/2018 

#pragma once

#include "SDL.h"

namespace neon_engine
{

	/*
	* Wrapper to use smart pointers with C-like SDL pointers.
	*/
	struct SdlDeleter {
		void operator()(SDL_Surface*  ptr) const { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture*  ptr) const { if (ptr) SDL_DestroyTexture(ptr); }
		void operator()(SDL_Renderer* ptr) const { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window*   ptr) const { if (ptr) SDL_DestroyWindow(ptr); }
	};

	template<class T, class D = std::default_delete<T>>
	struct SharedPtrWithDeleter : public std::shared_ptr<T>
	{
		explicit SharedPtrWithDeleter(T* t = nullptr) :
			std::shared_ptr<T>(t, D())
		{}

		void reset(T* t = nullptr) {
			std::shared_ptr<T>::reset(t, D());
		}

	};

	using SurfacePtr = SharedPtrWithDeleter<SDL_Surface, SdlDeleter>;
	using TextureSptr = SharedPtrWithDeleter<SDL_Texture, SdlDeleter>;
	using RendererSptr = SharedPtrWithDeleter<SDL_Renderer, SdlDeleter>;
	using WindowSptr = SharedPtrWithDeleter<SDL_Window, SdlDeleter>;
}