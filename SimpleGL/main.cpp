#include "SimpleGL.h"


int main()
{
	float x[4];
	float y[4];


	x[0] = 100;
	x[1] = 250;
	x[2] = 250;
	x[3] = 100;

    y[0] = 300;
	y[1] = 300;
	y[2] = 350;
	y[3] = 350;
	
	initGL(640,480);

	setFontSize(24);

	setColor(100,100,100);

    selectLayer(1);

	polygon(x,y,4);


	setColor(255,0,255);

	text(x[0] + 20 , y[0] + 18 , "Layer 1");

	for(int i=0;i<4;i++)
	{
	  x[i] += 40;
	  y[i] -= 30;
	}

	setColor(120,120,120);

    selectLayer(2);

	polygon(x,y,4);

	setColor(255,0,255);

	text(x[0] + 20 , y[0] + 18 , "Layer 2");

	for(int i=0;i<4;i++)
	{
	  x[i] += 40;
	  y[i] -= 30;
	}

	setColor(140,140,140);

    selectLayer(3);

	polygon(x,y,4);

	setColor(255,0,255);

	text(x[0] + 20 , y[0] + 18 , "Layer 3");

	for(int i=0;i<4;i++)
	{
	  x[i] += 20;
	  y[i] -= 10;
	}

	wait();

    end();
}