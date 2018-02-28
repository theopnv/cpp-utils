#include "WindowsUtility.h"

namespace windows_utility
{
	const std::string GetLastMessageError()
	{
		DWORD code = GetLastError();
		LPSTR buff = nullptr;
		size_t size = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, 
			code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&buff, 
			0, 
			NULL);
		
		std::string msg(buff, size);
		LocalFree(buff);

		return msg;
	}
}