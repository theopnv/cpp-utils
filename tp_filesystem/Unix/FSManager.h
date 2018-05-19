//
// Created by theo on 12/25/17. (Merry Xmas)
//

#ifndef CPP_ZIA_FSMANAGER_H
#define CPP_ZIA_FSMANAGER_H

#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../AFSManager.h"

namespace tp_filesystem
{
#define MAX_EVENTS  1024
#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (MAX_EVENTS*(EVENT_SIZE + 16))

	class FSManager : public AFSManager
	{

	private:
		int         _fd;
		std::string _path;

	public:
		bool    FSFileExists(const std::string& path) override;

		bool    FSOpen(const std::string& path) override;
		bool    FSClose() override;
		bool    FSRead(std::string& buff, int len) const override;
		bool    FSWrite(const std::string& msg) const override;
		bool	FSIsExtension(const std::string& path, constant::var constant) const override;
        void    FSNotifyWhenFileChanged(const std::string &dirPath,
                                                EventMap eventMap) override;
        std::list<std::string> 	FSListFilesInFolder(const std::string& dirPath) const override;
		std::string 			FSGetFolderFromPath(const std::string& path) const override;
		bool 	FSCreateDirectory(const std::string& path) const override;

    };

}

#endif //CPP_ZIA_FSMANAGER_H
