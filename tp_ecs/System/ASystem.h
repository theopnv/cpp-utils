#pragma once

#include "Entity.h"

namespace tp_ecs
{

	class ASystem
	{

	protected:
		EntityList	_entities;

	public:
		virtual		~ASystem() = default;

		virtual void	update();
		void			refresh();
		Sptr<Entity>	addEntity(const Sptr<Entity>& entity);

	};

}