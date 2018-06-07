//  Created by Theo Penavaire on 06/03/2018
//  Last Update on 06/08/2018 

#pragma once

#include <memory>
#include <functional>

namespace neon_engine
{
	template <class T>
	using Sptr = std::shared_ptr<T>;

	template <class T>
	using Uptr = std::unique_ptr<T>;

	template <class T>
	using Event = std::function<T>;
}