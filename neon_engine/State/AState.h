//  Created by Theo Penavaire on 06/09/2018
//  Last Update on 06/09/2018 

#include "IState.h"
#include "IUIObject.h"

namespace neon_engine
{
	
	class AState : public IState
	{
		
	public:
		virtual ~AState() = default;

	protected:
		Sptr<Core>						_ge;

		std::vector<Sptr<IUIObject>>	_gameObjects;
		NEventFuncMapper				_eventFuncMapper;

		virtual void setEventFuncMapper() = 0;
	};

}