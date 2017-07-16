#pragma once

struct ColorRGB
{
	int r;
	int g;
	int b;

	ColorRGB();
	ColorRGB(int R, int G, int B);
};

namespace Colors
{
	extern ColorRGB white;
	extern ColorRGB black;

	extern ColorRGB red;
	extern ColorRGB green;
	extern ColorRGB blue;

	extern ColorRGB cyan;
	extern ColorRGB magenta;
	extern ColorRGB yellow;
}