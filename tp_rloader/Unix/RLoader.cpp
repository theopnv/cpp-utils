//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#include "RLoader.h"

namespace tp_rloader
{
	std::string RLoader::getResourcesDir(const std::string& projectDir)
	{
		struct passwd *pw = getpwuid(getuid());
		const char *homedir = pw->pw_dir;

		std::string path(homedir);
		path.append("/" + projectDir + "/");
		return path;
	}

}