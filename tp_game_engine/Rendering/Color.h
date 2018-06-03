#pragma once

#include <map>

namespace tp_game_engine
{

	struct ColorLevel
	{
		int	r;
		int	g;
		int	b;
		int	a;
		ColorLevel() = default;
		ColorLevel(int r_, int g_, int b_, int a_) :
			r(r_), g(g_), b(b_), a(a_)
		{}
	};

	enum Color
	{
		apricot,		// #e4a672 
		bronze,			// #b86f50 
		brown,			// #743f39 
		byzantium,		// #3f2832 
		carmine,		// #9e2835 
		amaranth,		// #e53b44 
		amber,			// #fb922b 
		peach,			// #ffe762 
		spring_bud,		// #63c64d 
		green,			// #327345 
		teal,			// #193d3f 
		slate_grey,		// #4f6781 
		silver,			// #afbfd2 
		white,			// #ffffff 
		cyan,			// #2ce8f4 
		blue,			// #0484d1 

	};

	const std::map<Color, ColorLevel>	GameColors =
	{
		{ apricot, { 228, 166, 114, 255 } },
		{ bronze, { 184, 111, 80, 255 } },
		{ brown, { 116, 63, 57, 255 } },
		{ byzantium, { 63, 40, 50, 255 } },
		{ carmine, { 158, 40, 53, 255 } },
		{ amaranth, { 229, 59, 68, 255 } },
		{ amber, { 251, 146, 43, 255 } },
		{ peach, { 255, 231, 98, 255 } },
		{ spring_bud, { 99, 198, 77, 255 } },
		{ green, { 50, 115, 69, 255 } },
		{ teal, { 25, 61, 63, 255 } },
		{ slate_grey, { 79, 103, 129, 255 } },
		{ silver, { 175, 191, 210, 255 } },
		{ white, { 255, 255, 255, 255 } },
		{ cyan, { 44, 232, 244, 255 } },
		{ blue, { 4, 132, 209, 255 } }

	};

}