//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#pragma once

#include <string>
#include <functional>
#include <map>
#include <list>

namespace tp_filesystem
{

	/**
	 * \brief Events for the filesystem watcher
	 */
	namespace notify
	{
		enum event
		{
			file_created,
			file_modified,
			file_deleted,
		};
	}

	/**
	 * \brief OS-related constants for file extension
	 * Can be extended if more file formats are to be checked
	 */
	namespace constant
	{
		enum var
		{
			dynamic_lib, /* Will be .dll on WIN & .so on Linux */
		};
	}

	/**
	 * \brief Used to map a filesystem event to a callback.
	 * The parameter of the callback is the path of the file if it is accessible.
	 * Ex: Call `onFileCreated(const std::string& createdFilePath)` when notify::event::file_created is raised
	 */
	using FSEventCallback = std::function<void(const std::string& filePath)>;
	using EventMap = std::map<notify::event, FSEventCallback>;

	/**
	 * \brief Interface for file system management.
	 * API for Unix and Windows. Handling of open, close, read, write...
	 */
	class IFSManager
	{

	public:

		/**
		 * \brief Check if the specified file exists
		 * \param path path to the file
		 * \return true if file exists
		 */
		virtual bool	FSFileExists(const std::string& path) = 0;

		/**
		 * \brief Return true if the specified folder exists
		 * \param path path to the folder 
		 * \return true if folder exists
		 */
		virtual bool 	FSFolderExists(const std::string& path) const = 0;

		/**
		 * \brief Create and/or open the specified file.
		 * TODO: Flags management (TRUNC, OVERWRITE...)
		 * WARNING: For now, it overwrites files when writing in it.
		 * \param path path to the file
		 * \return true if operation succeeded
		 */
		virtual bool	FSOpen(const std::string& path) = 0;

		/**
		 * \brief Close the file and free the resource used by the FSManager
		 * \return true if operation succeeded
		 */
		virtual bool	FSClose() = 0;

		/**
		 * \brief Read the file used by the FSManager.
		 * Fill the buffer buff with len characters.
		 * \param buff placeholder for read data
		 * \param len length of buff
		 * \return true id operation succeeded
		 */
		virtual bool	FSRead(std::string& buff, int len) const = 0;

		/**
		 * \brief Write msg in the file used by the FSManager
		 * \param msg Message to write in file
		 * \return true if operation succeeded
		 */
		virtual bool	FSWrite(const std::string& msg) const = 0;

		/**
		 * \brief Check if the file has the specified extension
		 * \param path path to the file
		 * \param ext extension to check
		 * \return result of the query
		 */
		virtual bool 	FSIsExtension(const std::string& path, const std::string& ext) const = 0;

		/**
		* \brief Check if the file has the specified extension among the 
		* \param path path to the file
		* \param ext extension to check
		* \return result of the query
		*/
		virtual bool 	FSIsExtension(const std::string& path, constant::var constant) const = 0;

		/**
		 * \brief Get the file extension
		 * \param path path to file
		 * \return extension of the file
		 */
		virtual std::string	FSGetFileExtension(const std::string& path) const = 0;

		/**
		 * \brief Raise the callback function when the system monitored an eventon the dirPath folder.
		 * Check http://manpagesfr.free.fr/man/man7/inotify.7.html for more informations.
		 * \param dirPath path of the directory to watch
		 * \param eventMap map of events to fire under certain circumstances (cf. EventMap typedef)
		 */
		virtual void	FSNotifyWhenFileChanged(const std::string& dirPath,
												EventMap eventMap) = 0;

		/**
		 * \brief List files in specified directory
		 * \param dirPath path of directory
		 * \return list of file paths of the directory
		 */
		virtual std::list<std::string> 	FSListFilesInFolder(const std::string& dirPath) const = 0;

		/**
		 * \brief Get the directory path from a file name
		 * \param path path to the file
		 * \return path of the directory one level higher than the specified file
		 */
		virtual std::string 		FSGetFolderFromPath(const std::string& path) const = 0;

		/**
		 * \brief Create a directory. Return true if creation is successful
		 * \param path path of the directory to be created
		 * \return true if operation succeeded
		 */
		virtual bool	FSCreateDirectory(const std::string& path) const = 0;

	};
}