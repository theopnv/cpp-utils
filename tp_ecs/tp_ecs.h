#pragma once

#include <memory>
#include <functional>

namespace tp_ecs
{
	template <class T>
	using Sptr = std::shared_ptr<T>;

	template <class T>
	using Uptr = std::unique_ptr<T>;

	template <class T>
	using Event = std::function<T>;
}