#pragma once

#include "tp_game_engine.h"

namespace tp_game_engine
{
	class GEngine;

	class IGameState
	{
		
		public:

			virtual void	init(Sptr<GEngine>& ge) = 0;
			virtual void	cleanup() = 0;

			virtual void	pause() = 0;
			virtual void	resume() = 0;

			virtual void	handleEvents() = 0;
			virtual void	update() = 0;
			virtual void	draw() = 0;

			virtual void	changeState(Sptr<IGameState> state) = 0;

		protected:
			virtual ~IGameState() = default;
	};

}