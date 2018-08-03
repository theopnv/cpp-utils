#pragma once

#include "Singleton.h"
#include "Entity.h"

namespace tp_ecs
	
	class EntityManager : public tp_singleton::Singleton<EntityManager>
	{
		
	public:
		size_t	_id = 0;

	public:
		EntityManager() = default;
		~EntityManager() override = default;

		Sptr<Entity>	createEntity()
		{
			return std::make_shared<Entity>(_id++);
		}

	};

}
