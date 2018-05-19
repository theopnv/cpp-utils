//
// Created by roman on 2/14/18.
//

#include <iostream>
#include "FSManager.h"

namespace tp_filesystem {

    void FSManager::FSNotifyWhenFileChanged(const std::string &dirPath,
                                            EventMap eventMap)
    {
        int fd;

        fd = inotify_init();
        if (fd == -1)
            throw std::runtime_error("[NotifyWhenFileChanged] Error fd");

        struct stat info;
        if (stat(dirPath.c_str(), &info) == 0
            && info.st_mode & S_IFDIR)
        {
            int wd, length, i = 0;
            char buffer[BUF_LEN];

            wd = inotify_add_watch(fd, dirPath.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
            if (wd == -1)
                throw std::runtime_error("[NotifyWhenFileChanged] Error wd");
            length = read(fd, buffer, BUF_LEN);
            if (length < 0)
                throw std::runtime_error("[NotifyWhenFileChanged] Error read");
            while (i < length)
            {
                struct inotify_event *event = (struct inotify_event *)&buffer[i];

                if (event->len) {
                    std::cout << "event" << std::endl;
                    if (event->mask & IN_CREATE) {
                        eventMap.at(notify::file_created)(event->name);
                    } else if (event->mask & IN_DELETE) {
                        eventMap.at(notify::file_deleted)(event->name);
                    } else if (event->mask & IN_MODIFY) {
                        eventMap.at(notify::file_modified)(event->name);
                    }
                }
                i += EVENT_SIZE + event->len;
            }
            (void)inotify_rm_watch(fd, wd);
            (void)close(fd);
        } else {
            throw std::invalid_argument("[NotifyWhenFileChanged] Wrong path");
        }
    }
}