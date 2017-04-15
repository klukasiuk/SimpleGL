/*************************************************************************
 * SimpleGL - www.github.com/klukasiuk/simplegl
 * A simple graphics library for novice C/C++ programers
 * Based on : OpenGL , GLFW , SOIL and FTGL libraries
 *------------------------------------------------------------------------
 *
 * Copyright (c) 2015-2017 Konrad £ukasiuk
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

#pragma once

#include "input.h"
#include "color.h"

// Window maintence


// Initialization of graphic window
void initGL(int w , int h);

// Releasing resources
void end();

// Sleeping thread ( time in miliseconds )
void sleep(int miliseconds);

// Pause till any key is pressed
void wait();



// Settings


// Set color used to clear the screen with clear()
void setClearColor(double r , double g , double b);

// Set color used to clear the screen with clear()
void setClearColor(ColorRGB color);

// Sets point size
void setPointSize(float size);

// Loading font from file
void setFont(char * name);

// Setting font size
void setFontSize(int size);

// Setting double buffered mode(it needs to be set before initialization)
void setDoubleBuffered(bool state);

// Time from program start in miliseconds
double getTime();



// Input 


// Checking for events and inputs
void checkEvents();

// Setting Mouse Callback
void setMouseCallback(void(*MouseCallback)(int x, int y, MouseButton button, InputAction action));

// Setting Keyboard Callback
void setKeyboardCallback(void(*KeyboardCallback)(KeyboardKey key, InputAction action));

// Returns state of key
InputAction getKeyState(KeyboardKey key);



// Error handling


// Throws out message box with given message
void errorMsg(char * msg);

// Throws out message box with given message and ends program
void errorCritical(char * msg);



// Projection


// Sets view region to given coordinates
void view(float left , float top , float right , float bottom);

// Rotate view , angle in degrees
void viewRotate(float angle);

// Select current layer
void selectLayer(int layer);



// Drawing functions


// Point ( size is set by setPointSize() )
void point(float x , float y);

// Line between two points
void line(float x1 , float y1 , float x2 , float y2);

// Circle in given point with given radius
void circle(float x , float y , float r);

// Polygon ( array of x , array of y , number of vertices)
void polygon( float * x , float * y , int n);

// Drawing text in given place
void text(float x , float y , char * t);

// Clearing screnn with ClearColor
void clear();

// Sets RGB color ( 0 - 255 )
void setColor(int r , int g , int b);

// Sets RGB color
void setColor(ColorRGB color);

// Sets gray color ( 0 - 255 )
void setGray(int value);

// Swaping buffers , clearing screen and checking for events
void swap();



// Drawing images


// Loading image from file and returning its ID
int loadImage(char * path);

// Drawing image with given ID where x,y are coordinates of left bottom vertex
void drawImage(int ID , float x, float y, float width, float height);

// Drawing image with given ID where x,y are coordinates of left bottom vertex and rotation is in degrees
void drawImage(int ID, float x, float y, float width, float height, int rotation);

// Drawing image with given ID where x,y are coordinates of center of image
void drawImageCentered(int ID, float x, float y, float width, float height);

// Drawing image with given ID where x,y are coordinates of center of image and rotation is in degrees
void drawImageCentered(int ID, float x, float y, float width, float height, int rotation);

// Changes all pixels with given color to transparent
void keyColor(int ID , int r , int g , int b);

// Changes all pixels with given color to transparent
void keyColor(int ID, ColorRGB color);

// Saving screeshot with given name in .bmp format
void screenshot(char * filename);