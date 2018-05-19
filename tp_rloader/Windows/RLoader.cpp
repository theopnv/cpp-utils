#pragma once

#include "RLoader.h"

namespace tp_rloader
{

	const std::string RLoader::getResourcesDir(const std::string& projectDir)
	{
		WCHAR path[256];

		if (SUCCEEDED(SHGetFolderPathW(
			NULL,
			CSIDL_PROFILE,
			NULL,
			0,
			path))) {
			std::wstring ws(path);
			std::string homeDir(ws.begin(), ws.end());
			return homeDir + "\\" + projectDir + "\\";
		}
		return "";
	}

}