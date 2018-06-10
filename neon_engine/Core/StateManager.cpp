//  Created by Theo Penavaire on 05/29/2018
//  Last Update on 06/08/2018 

#include "Core.h"

namespace neon_engine
{

	void Core::cleanupStates()
	{
		while (!_states.empty()) {
			_states.top()->cleanup();
			_states.pop();
		}
	}

	void Core::changeState(const Sptr<IGameState>& state)
	{
		if (!_states.empty()) {
			_states.top()->cleanup();
			_states.pop();
		}

		_states.push(state);
		_states.top()->start(shared_from_this());
	}

	void Core::pushState(const Sptr<IGameState>& state)
	{
		if (!_states.empty()) {
			_states.top()->pause();
		}

		_states.push(state);
		_states.top()->start(shared_from_this());
	}

	void Core::popState()
	{
		if (!_states.empty()) {
			_states.top()->cleanup();
			_states.pop();
		}

		if (!_states.empty()) {
			_states.top()->resume();
		}
	}

	void Core::update(NEvent& event)
	{
		_states.top()->update(event);
	}

	void Core::draw()
	{
		_states.top()->draw();
	}
}