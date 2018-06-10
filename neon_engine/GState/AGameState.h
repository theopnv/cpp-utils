//  Created by Theo Penavaire on 06/09/2018
//  Last Update on 06/09/2018 

#include "IGameState.h"
#include "IGObject.h"

namespace neon_engine
{
	
	class AGameState : public IGameState
	{
		
	public:
		virtual ~AGameState() = default;

	protected:
		Sptr<Core>		_ge;

		std::vector<Sptr<IGObject>>	_gameObjects;
		NEventFuncMapper			_eventFuncMapper;

		virtual void setEventFuncMapper() = 0;
	};

}