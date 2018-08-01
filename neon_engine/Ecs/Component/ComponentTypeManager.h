#pragma once

namespace neon_engine::ecs
{

	using Id = std::size_t;

	class ComponentTypeManager
	{

	public:
		static Id getUniqueId()
		{
			static Id lastId = 0u;
			return lastId++;
		}

		template <class T>
		static Id getComponentType()
		{
			static Id typeId = getUniqueId();
			return typeId;
		}

	};

}