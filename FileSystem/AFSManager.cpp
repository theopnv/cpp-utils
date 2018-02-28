//
// Created by Theo on 2/15/2018.
//

#include "AFSManager.h"

namespace filesystem
{
	bool	AFSManager::FSIsExtension(const std::string& path,
									  const std::string& ext) const
	{
		return path.substr(path.find_last_of('.') + 1) == ext;
	}

	bool	AFSManager::FSFolderExists(const std::string &path) const
	{
		struct stat info;

		return stat(path.c_str(), &info) != 0 && (info.st_mode & S_IFDIR);
	}

	std::string	AFSManager::FSGetFileExtension(const std::string &path) const {
		return path.substr(path.find_last_of('.') + 1);
	}

}
