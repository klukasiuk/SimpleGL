#include "color_SGL.h"

void clamp(int & val, int min, int max)
{
	if (val < min)
		val = min;

	if (val > max)
		val = max;
}

ColorRGB::ColorRGB()
{
	r = 0;
	g = 0;
	b = 0;
}

ColorRGB::ColorRGB(int R, int G, int B)
{
	clamp(R, 0, 255);
	clamp(G, 0, 255);
	clamp(B, 0, 255);

	r = R;
	g = G;
	b = B;
}

namespace Colors
{
	ColorRGB white(255,255,255);
	ColorRGB black(0,0,0);

	ColorRGB red(255,0,0);
	ColorRGB green(0,255,0);
	ColorRGB blue(0,0,255);

	ColorRGB cyan(0,255,255);
	ColorRGB magenta(255, 0, 255);
	ColorRGB yellow(255, 255, 0);
}