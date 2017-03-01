#include "SimpleGL.h"
#include <cmath>


int main()
{
	setDoubleBuffered(true);

	initGL(640,480);

	setClearColor(80,128,255);

	int mario = loadImage("mario.png");
	int jump = loadImage("mario1.png");

	keyColor(mario,0,255,255);
	keyColor(jump,0,255,255);

	int y = 0;
	double time;

	while(1)
	{
	  for(int i=0;i<=64;i++)
	  {
	    y = 360* sin( i*(3.1415/64));

		drawImage(jump,300,y,64,48);

		swap();

	    sleep(16);
	  }
	  

	  drawImage(mario,300,0,64,48);

	  swap();

	  for(int i=0;i<10;i++)
	  {
	  sleep(200);
	  checkEvents();
	  }

	}


	wait();

    end();
}