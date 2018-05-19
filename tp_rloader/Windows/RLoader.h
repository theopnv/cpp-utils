#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <Shlobj.h>

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