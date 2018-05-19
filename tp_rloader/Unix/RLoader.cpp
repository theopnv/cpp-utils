//
// Created by theo on 1/24/18.
//

#include "RLoader.h"

namespace tp_rloader
{

	const std::string RLoader::getResourcesDir(const std::string& projectDir)
	{
		struct passwd *pw = getpwuid(getuid());
		const char *homedir = pw->pw_dir;

		std::string path(homedir);
		path.append("/" + projectDir + "/");
		return path;
	}

}