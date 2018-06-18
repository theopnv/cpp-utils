//  Created by Theo Penavaire on 05/31/2018
//  Last Update on 06/08/2018 

#pragma once

#include <cstddef>
#include <mutex>
#include <vector>
#include <queue>
#include <memory>
#include <functional>
#include "asio.hpp"

namespace tp_network
{
	using tcp = asio::ip::tcp;

	//using Byte = char;
	//using Packet = std::vector<Byte>;

	template <class T>
	using Event = std::function<T>;

	template <class T>
	using Sptr = std::shared_ptr<T>;

	struct OperationResult
	{
		std::string		message;
		bool			success;

		OperationResult(const std::string& msg, bool s = true) :
			message(msg), success(s)
		{}
		OperationResult() = default;
	};
}
