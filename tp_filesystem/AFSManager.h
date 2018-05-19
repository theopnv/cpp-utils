//
// Created by Theo on 2/15/2018.
//

#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include "IFSManager.h"

namespace tp_filesystem
{

	class AFSManager : public IFSManager
	{

	public:
		virtual ~AFSManager() = default;
		AFSManager() = default;

		bool	FSIsExtension(const std::string& path, const std::string& ext) const override;
		bool 	FSFolderExists(const std::string& path) const override;
		std::string	FSGetFileExtension(const std::string& path) const override;

	};
}

