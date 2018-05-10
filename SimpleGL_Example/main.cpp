/*************************************************************************
* SimpleGL Example - www.github.com/klukasiuk/simplegl
* App demostrating usage of SimpleGL library, it implements animation of jumping character
* Based on : OpenGL , GLFW , SOIL and FTGL libraries
*------------------------------------------------------------------------
*
* Copyright (c) 2015-2018 Konrad £ukasiuk
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the author be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would
*    be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not
*    be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source
*    distribution.
*
*************************************************************************/

#include "SimpleGL.h"
#include <cmath>

// Main loop statement
bool run;

// Handles for images of mario in two states
int mario_standing;
int mario_jumping;

// Ground images
int ground;
int ground2;

// Variable for storing marios state
float mario_pos;
float mario_height;
float mario_rotation;
int mario_rotation_dir;
bool mario_going_left;
bool mario_going_right;

// Constants for tweaking jumping animation
const int mario_horizontal_speed = 5;
const int jump_period = 3000;
const int standing_time = 1000;
const int ground_clamping = 10;
const int sleep_time = 16;

// Function called every time key was pressed
void myKeyboardCallback(KeyboardKey key, InputAction action)
{
	if (key == Key_Space && action == Pressed)
		if (mario_height == 0)
			mario_rotation_dir *= -1;

	if (key == Key_Left && action == Pressed && mario_going_right == false)
		mario_going_left = true;

	if (key == Key_Left && action == Released)
		mario_going_left = false;

	if (key == Key_Right && action == Pressed && mario_going_left == false)
		mario_going_right = true;

	if (key == Key_Right && action == Released)
		mario_going_right = false;
}

// Function called every time mouse button was pressed
void myMouseCallback(int x, int y, MouseButton button, InputAction action)
{
	if (button == Mouse_Left && action == Pressed)
		viewRotate(10.0f);

	if (button == Mouse_Right && action == Pressed)
		viewRotate(-10.0f);
}

// Initialization function
void init()
{
	// Setting hint for library to use double buffering ( swapping buffers will be needed)
	setDoubleBuffered(true);

	// Initialization of graphics window with desired size of window
	initGL(640, 480, "SimpleGL - Mario Example");

	// Setting color used when we clear window
	setClearColor(80, 128, 255);

	// Loading two images of mario(standing and jumping) , we must catch image ID to use it later
	mario_standing = loadImage("mario.png");
	mario_jumping = loadImage("mario1.png");

	// Loading ground images
	ground = loadImage("ground.png");
	ground2 = loadImage("ground2.png");

	// keyColor makes every pixel in image with given color completly transparent
	keyColor(mario_standing, 0, 255, 255);
	keyColor(mario_jumping, 0, 255, 255);

	// Now main loop flag can be set to True
	run = true;

	// Setting mario_height and mario_rotation(degrees) to zero at start and other state variables
	mario_height   = 0.0f;
	mario_rotation = 0.0f;
	mario_pos = 320.0f;
	mario_rotation_dir = 1;
	mario_going_left = false;
	mario_going_right = false;

	// We must register our input callbacks if we want them work
	setKeyboardCallback(myKeyboardCallback);
	setMouseCallback(myMouseCallback);
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
	int time = (int)getTime();

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
		mario_height = 320 * sinf(time*(3.14159/ (jump_period - standing_time)));
		mario_rotation = mario_rotation_dir * 360.0f * time / (jump_period - standing_time);

		// If mario is near ground height is clamped to zero to prevent jittering
		if (mario_height < ground_clamping)		
		{
			mario_height = 0;
			mario_rotation = 0;
		}
	}

	if (mario_going_left)
		if (mario_pos > 120)
			mario_pos -= mario_horizontal_speed;

	if (mario_going_right)
		if (mario_pos < 520)
			mario_pos += mario_horizontal_speed;

	sleep(sleep_time);
}

// This function is drawing everything and swaping buffers if there is double buffering
void draw()
{
	// If mario is on ground draw standing mario image
	if( mario_height == 0)
	drawImageCentered(mario_standing, mario_pos, 96, 48, 64, mario_rotation);

	// If mario is in air draw jumping mario image with some rotation
	else
	drawImageCentered(mario_jumping, mario_pos, mario_height + 96 , 64, 48, mario_rotation);

	// Drawing ground under mario
	for(int i=0;i<20;i++)
	drawImage(ground, i * 32, 32, 32, 32);

	for (int i = 0; i<20; i++)
	drawImage(ground2, i * 32, 0, 32, 32);

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