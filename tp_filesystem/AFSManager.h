//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#pragma once

#include "IFSManager.h"

namespace tp_filesystem
{

	/**
	 * \brief Abstract class for FileSystem Manager (used by Unix and Windows classes)
	 */
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

