//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include "RLoader.h"

namespace tp_rloader
{
	/**
	 * \brief Return the absolute path of a directory from the user's ${HOME} folder. 
	 * Keep in mind that this environment variable must be set, particularly on windows.
	 * \param projectDir Relative path of the directory to get (from ${HOME}). 
	 * E.g. to get ".appData", located in "C:/Users/John/"
	 * \return Absolute path to the specified folder
	 */
	std::string RLoader::getResourcesDir(const std::string& projectDir)
	{
		WCHAR path[256];

		if (SUCCEEDED(SHGetFolderPathW(
			NULL,
			CSIDL_PROFILE,
			NULL,
			0,
			path))) {
			std::wstring ws(path);
			const std::string homeDir(ws.begin(), ws.end());
			return homeDir + "\\" + projectDir + "\\";
		}
		return "";
	}

}