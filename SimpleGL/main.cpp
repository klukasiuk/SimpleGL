#include "SimpleGL.h"
#include <cmath>

// Main loop statement
bool run;

// Handles for images of mario in two states
int mario_standing;
int mario_jumping;

// Variable for storing marios height above ground
int mario_height;
int mario_rotation;

// Constants for tweaking jumping animation
const int jump_period = 3000;
const int standing_time = 1000;
const int ground_clamping = 10;
const int sleep_time = 30;

// Initialization function
void init()
{
	// Setting hint for library to use double buffering ( swapping buffers will be needed)
	setDoubleBuffered(true);

	// Initialization of graphics window with desired size of window
	initGL(640, 480);

	// Setting color used when we clear window
	setClearColor(80, 128, 255);

	// Loading two images of mario(standing and jumping) , we must catch image ID to use it later
	mario_standing = loadImage("mario.png");
	mario_jumping = loadImage("mario1.png");

	// keyColor makes every pixel in image with given color completly transparent
	keyColor(mario_standing, 0, 255, 255);
	keyColor(mario_jumping, 0, 255, 255);

	// Now main loop flag can be set to True
	run = true;

	// Setting mario_height and mario_rotation(degrees) to zero at start
	mario_height = 0;
	mario_rotation = 0;
}

// Closing function
void release()
{
	// Waiting for users input
	wait();

	// Releasing resources and closing window
	end();
}

// Getting input and input handling
void input()
{
	// Checking for new events and inputs
	checkEvents();
}

// Updating program state
void update()
{
	int time = (int)(getTime()*1000);

	// Getting time in animation period
	time = time % jump_period;

	// Divided animation period into two states : standing and jumping
	if (time < standing_time)
	{
		mario_height = 0;
		mario_rotation = 0;
	}
	else
	{
		time = time - standing_time;
		mario_height = 360 * sin(time*(3.14159/ (jump_period - standing_time)));
		mario_rotation = 360.0 * time / (jump_period - standing_time);

		// If mario is near ground height is clamped to zero to prevent jittering
		if (mario_height < ground_clamping)		
		{
			mario_height = 0;
			mario_rotation = 0;
		}
	}

	sleep(sleep_time);
}

// This function is drawing everything and swaping buffers if there is double buffering
void draw()
{
	// If mario is on ground draw standing mario image
	if( mario_height == 0)
	drawImageCentered(mario_standing, 320, 32, 48, 64, mario_rotation);

	// If mario is in air draw jmping mario image with some rotation
	else
	drawImageCentered(mario_jumping, 320, mario_height + 32 , 64, 48, mario_rotation);

	// Swap buffers to show what was drawed
	swap();
}

// Main loop is really simple and self explaining 
int main()
{
	init();

	while(run)
	{
		input();

		update();

		draw();
	}

	release();
}