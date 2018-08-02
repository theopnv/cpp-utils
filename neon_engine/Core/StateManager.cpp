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

	void Core::changeState(const Sptr<IState>& state)
	{
		_popState = true;

		_states.push(state);
	}

	void Core::pushState(const Sptr<IState>& state)
	{
		_popState = true;

		_states.push(state);
	}

	void Core::popState()
	{
		_popState = true;

		if (!_states.empty()) {
			_states.top()->resume();
		}
	}

	void Core::update(NEvent& event)
	{
		if (!_states.empty()) {
			_states.top()->update(event);
		}
	}

	void Core::draw()
	{
		if (!_states.empty()) {
			_states.top()->draw();
		}
	}
}