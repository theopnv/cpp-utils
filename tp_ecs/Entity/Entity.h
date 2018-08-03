//  Created by Theo Penavaire on 08/01/2018
//  Last Update on 08/01/2018 

#pragma once

#include <string>
#include <map>
#include <vector>
#include "AComponent.h"
#include "ComponentException.h"

namespace tp_ecs
{
	
	using ComponentMap = std::map<const std::string, Sptr<AComponent>>;

	class Entity : std::enable_shared_from_this<Entity>
	{
		
	private:
		std::size_t		_id;

	public:
		bool			_isActive = true;
		ComponentMap	_components;

		explicit Entity(std::size_t id);
		~Entity() = default;

		void			update();
		bool			isActive() const;
		void			destroy();

		template <class T>
		bool			hasComponent() const
		{
			auto name = typeid(T).name();
			return _components.count(name);
		}

		template <class T, class... TArgs>
		Sptr<T>			addComponent(TArgs&&... args)
		{
			auto component = std::make_shared<T>(std::forward<TArgs>(args)...);
			component->entity = this;

			auto name = typeid(T).name();
			auto comp = _components.insert(
				std::pair<const std::string, Sptr<AComponent>>(
					name, component));

			component->init();
			return std::dynamic_pointer_cast<T>(comp);
		}

		template <class T>
		Sptr<T>			getComponent() const
		{
			if (!hasComponent<T>()) {
				std::string msg("Component of type '");
				msg.append(typeid(T).name());
				msg.append("' not found");
				throw new ComponentNotFoundException(msg);
			}

			auto comp(_components.at(typeid(T).name()));
			return std::dynamic_pointer_cast<T>(comp);
		}

	};

	using EntityList = std::vector<Sptr<Entity>>;

}
