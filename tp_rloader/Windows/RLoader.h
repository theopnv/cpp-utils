//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

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

		static std::string	getResourcesDir(const std::string& projectDir);

	};

}