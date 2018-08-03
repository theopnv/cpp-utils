#include <functional>
#include <algorithm>
#include "ASystem.h"

namespace tp_ecs
{

	void ASystem::update()
	{
		for (auto& e : _entities) {
			e->update();
		}
	}

	void ASystem::refresh()
	{
		_entities.erase(
			std::remove_if(
				std::begin(_entities),
				std::end(_entities),
				[](const Sptr<Entity>& entity)
				{
					return !entity->isActive();
				}),
			std::end(_entities)
		);
	}

	Sptr<Entity>	ASystem::addEntity(const Sptr<Entity>& entity)
	{
		_entities.emplace_back(entity);
		return entity;
	}

}