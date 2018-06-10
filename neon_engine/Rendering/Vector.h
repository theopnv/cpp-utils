//  Created by Theo Penavaire on 05/20/2018
//  Last Update on 06/08/2018 

#pragma once

namespace neon_engine
{

	/**
	 * \brief Vector representing a coordinate in space (2D)
	 * \tparam T 
	 */
	template <class T>
	struct Vector2
	{
		// For x and y (size)
		T x() const { return a; }
		void x(const T x) { a = x; }
		T y() const { return b; }
		void y(const T y) { b = y; }

		// For width and height (pos)
		T w() const { return a; }
		void w(const T w) { a = w; }
		T h() const { return b; }
		void h(const T h) { b = h; }

		Vector2() = default;
		Vector2(const T a_, const T b_) : a(a_), b(b_) {}

		bool	operator==(const Vector2& other) const 
		{
			return this->a == other.a && this->b == other.b;
		}

	private:
		T	a;
		T	b;

	};

	/**
	 * \brief Vector representing coordinates and size (2D)
	 * \tparam T 
	 */
	template <class T>
	struct Vector4
	{
		Vector2<T>		pos;
		Vector2<T>		size;

		Vector4() = default;
		Vector4(const Vector2<T> pos_, const Vector2<T> size_) :
			pos(pos_),
			size(size_)
		{}
		Vector4(const T x, const T y, const T w = 0, const T h = 0) :
			pos({ x, y }),
			size({ w, h })
		{}

		bool operator==(const Vector4& other) const {
			return other.pos == this->pos && other.size == this->size;
		}
	};

}