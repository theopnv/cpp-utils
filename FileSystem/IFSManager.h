#pragma once

#include <string>
#include <functional>
#include <map>
#include <list>

namespace filesystem
{

	namespace notify
	{
		enum event
		{
			file_created,
			file_modified,
			file_deleted,
		};
	}

	namespace constant
	{
		enum var
		{
			dynamic_lib,
			php,
		};
	}

	/*
	** Used to map a filesystem event to a callback.
	** The parameter of the callback is the path to the library if it is accessible.
	** Ex: Call onFileCreated() when notify::event::file_created is raised
	*/
	using FSEventCallback = std::function<void (const std::string& dlPath)>;
	using EventMap = std::map<notify::event, FSEventCallback>;

	/*
	** Interface for file system management.
	** API for Unix and Windows. Handling of open, close, read, write...
	*/
	class IFSManager
	{

	public:

		/* 
		** Return true if the specified file exists
		*/
		virtual bool	FSFileExists(const std::string& path) = 0;

		/*
		 * Return true if the specified folder exists
		 */
		virtual bool 	FSFolderExists(const std::string& path) const = 0;

		/*
		** Create and/or open the specified file.
		** TODO: Flags management (TRUNC, OVERWRITE...)
		** WARNING: For now, it overwrites files when writing in it.
		*/
		virtual bool	FSOpen(const std::string& path) = 0;

		/*
		** Close the file and free the resource used by the FSManager
		*/
		virtual bool	FSClose() = 0;

		/*
		** Read the file used by the FSManager.
		** Fill the buffer buff with len characters.
		*/
		virtual bool	FSRead(std::string& buff, int len) const = 0;

		/*
		** Write msg in the file used by the FSManager
		*/
		virtual bool	FSWrite(const std::string& msg) const = 0;

		/*
		 * Returns true if path has the same extension as ext or constant
		 */
		virtual bool 	FSIsExtension(const std::string& path, const std::string& ext) const = 0;
		virtual bool 	FSIsExtension(const std::string& path, constant::var constant) const = 0;

		/*
		 * Return the extension of the file
		 */
		virtual std::string	FSGetFileExtension(const std::string& path) const = 0;

		/*
		** Raise the callback function when the system monitored an event
		** on the dirPath folder.
		** Check http://manpagesfr.free.fr/man/man7/inotify.7.html for more informations.
		*/
		virtual void	FSNotifyWhenFileChanged(const std::string& dirPath,
												EventMap eventMap) = 0;

		/*
		 * List files in specified directory
		 */
		virtual std::list<std::string> 	FSListFilesInFolder(const std::string& dirPath) const = 0;

		/*
		 * Get the directory path from a file name
		 */
		virtual std::string 		FSGetFolderFromPath(const std::string& path) const = 0;

		/*
		 * Create a directory. Return true if creation is successful
		 */
		virtual bool	FSCreateDirectory(const std::string& path) const = 0;

	};
}