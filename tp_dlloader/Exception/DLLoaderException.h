//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/07/2018 

#pragma once

#include <exception>
#include <string>

namespace exception
{

	/**
	 * \brief Exception thrown by the DLLoader
	 */
	class DLLoaderException : public std::exception
	{
	  private:
		std::string	_message;

	  public:
		explicit DLLoaderException(const std::string &e) throw();
		DLLoaderException() throw() = default;
		virtual		~DLLoaderException() throw() = default;


		const char *what() const throw() override;
	};

}
