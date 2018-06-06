#include "GEngine.h"

namespace tp_game_engine
{

	void GEngine::cleanup()
	{
		while (!_states.empty()) {
			_states.top()->cleanup();
			_states.pop();
		}
	}

	void GEngine::changeState(Sptr<IGameState> state)
	{
		if (!_states.empty()) {
			_states.top()->cleanup();
			_states.pop();
		}

		_states.push(state);
		_states.top()->init(shared_from_this());
	}

	void GEngine::pushState(Sptr<IGameState> state)
	{
		if (!_states.empty()) {
			_states.top()->pause();
		}

		_states.push(state);
		_states.top()->init(shared_from_this());
	}

	void GEngine::popState()
	{
		if (!_states.empty()) {
			_states.top()->cleanup();
			_states.pop();
		}

		if (!_states.empty()) {
			_states.top()->resume();
		}
	}

	void GEngine::update()
	{
		_states.top()->update();
	}

	void GEngine::draw()
	{
		_states.top()->draw();
	}
}