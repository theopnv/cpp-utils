#pragma once

#include <Windows.h>
#include "AFSManager.h"

namespace filesystem
{

	class FSManager : public AFSManager
	{

	private:
		static const int MAX_BUFFER = 4096;

		HANDLE	_handle;
		std::string	_path;

	public:
		bool	FSFileExists(const std::string& path) override;

		bool	FSOpen(const std::string& path) override;
		bool	FSClose() override;
		bool	FSRead(std::string& buff, int len) const override;
		bool	FSWrite(const std::string& msg) const override;

		void	FSNotifyWhenFileChanged(const std::string& dirPath,
										EventMap eventMap) override;
		bool	FSIsExtension(const std::string& path, constant::var constant) const override;
		std::list<std::string> 	FSListFilesInFolder(const std::string& dirPath) const override;
		std::string 			FSGetFolderFromPath(const std::string& path) const override;
		bool	FSCreateDirectory(const std::string& path) const override;

	};
}