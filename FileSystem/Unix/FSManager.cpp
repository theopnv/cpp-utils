//
// Created by theo on 12/25/17. (Merry Xmas)
//

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <dirent.h>
#include "FSManager.h"

namespace filesystem
{

	bool FSManager::FSFileExists(const std::string &path)
	{
		struct stat buffer {};
		return (stat (path.c_str(), &buffer) == 0);
	}

	bool FSManager::FSOpen(const std::string &path)
	{
		_path = path;
		_fd = open(path.c_str(), O_RDWR | O_CREAT, 0644);
		if (_fd == -1) {
			std::cerr << "[FILESYSTEM ERROR] Can't open " << _path << std::endl;
			return false;
		}

		return true;
	}

	bool FSManager::FSClose()
	{
		if (close(_fd) == -1) {
			std::cerr << "[FILESYSTEM ERROR] Can't close " << _path << std::endl;
			return false;
		}
		return true;
	}

	bool FSManager::FSRead(std::string &buff, int len) const
	{
		char tmpBuff[len + 1];

		ssize_t nbRead = read(_fd, tmpBuff, static_cast<size_t>(len));
		if (nbRead == -1)
		{
			std::cerr << "[FILESYSTEM ERROR] Can't read " << _path << std::endl;
			return false;
		}
		tmpBuff[nbRead] = 0;
		buff = tmpBuff;
		return true;
	}

	bool FSManager::FSWrite(const std::string &msg) const
	{
		ssize_t nbWritten = write(_fd, msg.c_str(), msg.size());
		if (nbWritten == -1)
		{
			std::cerr << "[FILESYSTEM ERROR] Can't write in " << _path << std::endl;
			return false;
		}
		return true;
	}
	
	bool FSManager::FSIsExtension(const std::string& path,
								  constant::var constant) const
	{
		switch (constant) {
			case (constant::dynamic_lib):
				return path.substr(path.find_last_of('.') + 1) == "so";
				break;
			case (constant::php):
				return path.substr(path.find_last_of('.') + 1) == "php";
				break;
		}
		return false;
	}

	std::list<std::string> FSManager::FSListFilesInFolder(const std::string &dirPath) const
	{
		DIR* dir;
		struct dirent *dirent;
		std::list<std::string> filesList;

		dir = opendir(dirPath.c_str());
		if (dir == NULL)
			throw std::invalid_argument("[FSListExistingModulesOnBoot] Error dir");
		while ((dirent = readdir(dir)) != NULL) {
			filesList.emplace_back(dirent->d_name);
		}
		closedir (dir);
		return filesList;
	}

	std::string FSManager::FSGetFolderFromPath(const std::string& path) const
	{
		std::string directory;
		const size_t last_slash_idx = path.rfind('/');
		if (std::string::npos != last_slash_idx)
		{
			directory = path.substr(0, last_slash_idx);
		}
		return directory;
	}

	bool FSManager::FSCreateDirectory(const std::string& path) const
	{
		mode_t nMode = 0733;
		int nError = 0;

		return mkdir(path.c_str(),nMode) == 0;

	}

}
