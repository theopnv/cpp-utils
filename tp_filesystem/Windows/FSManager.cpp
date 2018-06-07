//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#include <iostream>
#include "FSManager.h"

namespace tp_filesystem
{

	bool FSManager::FSFileExists(const std::string& path)
	{
		DWORD dwAttrib = GetFileAttributes(path.c_str());

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}

	bool FSManager::FSOpen(const std::string& path)
	{
		_path = path;
		HANDLE	handle;

		handle = CreateFile(
			_path.c_str(),
			GENERIC_ALL,
			FILE_SHARE_READ,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (handle == INVALID_HANDLE_VALUE) {
			std::cerr << "[FILESYSTEM ERROR] Can't open " << _path << std::endl;
			return false;
		}

		_handle = handle;
		return true;
	}

	bool FSManager::FSClose()
	{
		if (!CloseHandle(_handle)) {
			std::cerr << "[FILESYSTEM ERROR] Can't close " << _path << std::endl;
			return false;
		}

		return true;
	}

	bool FSManager::FSRead(std::string& buff, int len) const
	{
		char	*tmpBuff = new char[len + 1];
		DWORD	nbRead;

		if (!ReadFile(_handle, tmpBuff, len, &nbRead, NULL)) {
			std::cerr << "[FILESYSTEM ERROR] Can't read " << _path << std::endl;
			return false;
		}

		tmpBuff[nbRead] = 0;
		buff = tmpBuff;
		delete[] tmpBuff;

		return true;
	}

	bool FSManager::FSWrite(const std::string& msg) const
	{
		DWORD	nbWritten;

		if (!WriteFile(_handle, (LPCVOID)msg.c_str(), (DWORD)msg.size(), &nbWritten, NULL)) {
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
				return path.substr(path.find_last_of('.') + 1) == "dll";
				break;
		}
		return false;
	}

	std::list<std::string> FSManager::FSListFilesInFolder(
			const std::string &dirPath) const
	{
		std::list<std::string> list;
		std::string path = dirPath + "*";
		WIN32_FIND_DATA data;
		HANDLE hFind = FindFirstFile(path.c_str(), &data);      // DIRECTORY

		if ( hFind != INVALID_HANDLE_VALUE ) {
			do {
				list.push_back(data.cFileName);
			} while (FindNextFile(hFind, &data));
			FindClose(hFind);
		}
		return list;
	}

	std::string FSManager::FSGetFolderFromPath(const std::string& path) const
	{
		std::string directory;
		const size_t last_slash_idx = path.rfind('\\');
		if (std::string::npos != last_slash_idx)
		{
			directory = path.substr(0, last_slash_idx);
		}
		return directory;
	}

	bool FSManager::FSCreateDirectory(const std::string &path) const
	{
		int nError = 0;

		return CreateDirectory(path.c_str(), NULL) == 0;
	}

}