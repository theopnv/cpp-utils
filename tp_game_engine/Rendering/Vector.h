#pragma once

namespace tp_game_engine
{

	template <class T>
	struct Vector2
	{
		// For x and y (size)
		T x() { return a; }
		void x(T x) { a = x; }
		T y() { return b; }
		void y(T y) { b = y; }

		// For width and height (pos)
		T w() { return a; }
		void w(T w) { a = w; }
		T h() { return b; }
		void h(T h) { b = h; }

		Vector2() = default;
		Vector2(T a_, T b_) : a(a_), b(b_) {}

		bool	operator==(const Vector2& other)
		{
			return this->a == other.a && this->b == other.b;
		}

	private:
		T	a;
		T	b;

	};

	template <class T>
	struct Vector4
	{
		Vector2<T>		pos;
		Vector2<T>		size;

		Vector4() = default;
		Vector4(Vector2<T> pos_, Vector2<T> size_) :
			pos(pos_),
			size(size_)
		{}
		Vector4(T x, T y, T w, T h) :
			pos({ x, y }),
			size({ w, h })
		{}

		bool operator==(const Vector4& other) {
			return other.pos == this->pos && other.size == this->size;
		}
	};

}