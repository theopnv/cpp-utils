//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#include <iostream>
#include "FSManager.h"

namespace tp_filesystem
{

	 void FSManager::FSNotifyWhenFileChanged(const std::string &dirPath,
											 EventMap eventMap)
	{
		DWORD nRet;
		bool result = true;

		LPCSTR lpcstrDirPath = dirPath.c_str();

		HANDLE dir = CreateFile(lpcstrDirPath,
								GENERIC_READ|FILE_LIST_DIRECTORY,
								FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
								nullptr,
								OPEN_EXISTING,
								FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED,
								nullptr);

		if (dir == INVALID_HANDLE_VALUE) {
			return ; 
		}

		OVERLAPPED PollingOverlap;
		FILE_NOTIFY_INFORMATION pNotify[1024];

		PollingOverlap.OffsetHigh = 0;
		PollingOverlap.hEvent = CreateEvent(nullptr, true, false, nullptr);

		while (result) {
			memset(pNotify[0].FileName, 0, sizeof(pNotify[0].FileName));
			result = (bool)ReadDirectoryChangesW(
					dir,
					(LPVOID)&pNotify,
					sizeof(pNotify),
					true,
					FILE_NOTIFY_CHANGE_FILE_NAME |
					FILE_NOTIFY_CHANGE_DIR_NAME |
					FILE_NOTIFY_CHANGE_SIZE |
					FILE_NOTIFY_CHANGE_LAST_WRITE |
					FILE_NOTIFY_CHANGE_LAST_ACCESS |
					FILE_NOTIFY_CHANGE_CREATION |
					FILE_NOTIFY_CHANGE_ATTRIBUTES,
					&nRet,
					&PollingOverlap,
					nullptr
			);

			WaitForSingleObject(PollingOverlap.hEvent, INFINITE);
			
			pNotify[0].FileName[pNotify[0].FileNameLength / 2] = 0;
			std::wstring tmp(pNotify[0].FileName);
			std::string fileName(tmp.begin(), tmp.end());
			switch(pNotify->Action)
			{
				case FILE_ACTION_ADDED:
					eventMap.at(notify::file_created)(fileName);
					break;
				case FILE_ACTION_REMOVED:
					eventMap.at(notify::file_deleted)(fileName);
					break;
				case FILE_ACTION_MODIFIED:
					eventMap.at(notify::file_modified)(fileName);
					break;
				default:
				std::cerr << "[NotifyWhenFileChanged] Error" << std::endl;
					break;
			}
		}

		CloseHandle(dir);

	}

}