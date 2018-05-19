//
// Created by theo on 1/24/18.
//

#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string>

namespace tp_rloader
{

	class RLoader
	{

	public:
		~RLoader() = default;
		RLoader() = default;

		static const std::string	getResourcesDir(const std::string& projectDir);

	};
}

