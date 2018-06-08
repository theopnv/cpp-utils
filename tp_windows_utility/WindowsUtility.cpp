//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#include "WindowsUtility.h"

namespace tp_windows_utility
{
	/**
	 * \brief Get the last winAPI error message, as a human readable string
	 * \return error message
	 */
	std::string GetLastMessageError()
	{
		const auto code = GetLastError();
		LPSTR buff = nullptr;
		const size_t size = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, 
			code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPSTR>(&buff), 
			0,
			nullptr);
		
		std::string msg(buff, size);
		LocalFree(buff);

		return msg;
	}
}