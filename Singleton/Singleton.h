//
// Created by Theo on 1/17/2018.
//

#pragma once

#include "../utility.h"

namespace singleton
{

	template <class T>
	class Singleton
	{

	private:
		static Sptr<T>	_instance;

	public:
		Singleton() = default;

		virtual ~Singleton() = default;

		static Sptr<T> getInstance()
		{
			if (!_instance) {
				_instance = std::make_shared<T>();
			}

			return _instance;
		}

	};

	template <class T>
	Sptr<T> Singleton<T>::_instance = nullptr;

}