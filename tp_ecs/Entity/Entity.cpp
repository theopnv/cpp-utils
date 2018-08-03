#include "Entity.h"

namespace tp_ecs
{
	
	Entity::Entity(std::size_t id) :
		_id(id)
	{}

	void Entity::update()
	{
		for (auto& c: _components) {
			c.second->update();
		}
	}

	bool Entity::isActive() const
	{
		return _isActive;
	}

	void Entity::destroy()
	{
		_isActive = false;
	}


}