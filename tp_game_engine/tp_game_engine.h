#pragma once

#include <memory>
#include <functional>

namespace tp_game_engine
{
	template <class T>
	using Sptr = std::shared_ptr<T>;

	template <class T>
	using Uptr = std::unique_ptr<T>;

	template <class T>
	using Event = std::function<T>;
}