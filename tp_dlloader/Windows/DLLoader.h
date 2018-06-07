//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#pragma once

#include <iostream>
#include "IDLLoader.h"
#include "Windows.h"
#include "DLLoaderException.h"
#include "WindowsUtility.h"

namespace tp_dlloader
{
	/**
	 * \brief Dynamic library loader
	 * \tparam T The type of class to load
	 */
	template <class T>
	class DLLoader : public IDLLoader<T>
	{

	private:
		HMODULE			_handle;
		std::string		_pathToLib;
		std::string		_allocClassSymbol;
		std::string		_deleteClassSymbol;

	public:
		DLLoader(std::string const &pathToLib,
			std::string const &allocClassSymbol = "allocator",
			std::string const &deleteClassSymbol = "deleter") :
			_handle(nullptr), _pathToLib(pathToLib),
			_allocClassSymbol(allocClassSymbol), _deleteClassSymbol(deleteClassSymbol)
		{}

		DLLoader() = default;
		~DLLoader() = default;

		void DLOpenLib() override
		{
			if (!(_handle = LoadLibrary(_pathToLib.c_str()))) {
				throw exception::DLLoaderException(windows_utility::GetLastMessageError());
			}
		}

		std::shared_ptr<T> DLGetInstance() override
		{
			using allocClass = T * (*)();
			using deleteClass = void(*)(T *);

			auto allocFunc = reinterpret_cast<allocClass>(
				GetProcAddress(_handle, _allocClassSymbol.c_str()));
			auto deleteFunc = reinterpret_cast<deleteClass>(
				GetProcAddress(_handle, _deleteClassSymbol.c_str()));

			if (!allocFunc || !deleteFunc) {
				DLCloseLib();
				throw exception::DLLoaderException(windows_utility::GetLastMessageError());
			}

			return std::shared_ptr<T>(
				allocFunc(),
				[deleteFunc](T *p) { deleteFunc(p); });
		}

		void DLCloseLib() override
		{
			if (FreeLibrary(_handle) == 0) {
				throw exception::DLLoaderException(windows_utility::GetLastMessageError());
			}
		}

	};

}