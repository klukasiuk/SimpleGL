#include "SimpleGL.h"

// Macros

#define PI       3.14159265358979323846       

// Std libraries ( chrono i thread -> C++11 )

#include <math.h>                   // math functions
#include <vector>                   // dynamic array -> vector
#include <chrono>                   // function Sleep
#include <thread>                   // function Sleep
#include <string>                   // Very handy in working with text

// Additional libs to OpenGL

#include <FTGL/FTGL/ftgl.h>			// text drawing
#include <SOIL/SOIL.h>				// loading images
#include <GLFW/glfw3.h>				// window and os handling


// Abstraction layer between os (windows.h) and this namespace
// Msgbox is used in error handling
#include "msgbox_SGL.h"


// Loading names

using std::string;
using std::to_string;
using std::vector;


// Global state variables

GLFWwindow * window = NULL;         // Handle for window
FTGLPixmapFont * font = NULL;       // Handle for font

int window_height;                  // Window dimmensions
int window_width;

int fontSize = 12;                  // Default font size
int layers = 3;						// Amount of layers

int currentlayer = 1;				// Current layer     

float lastCameraPosX;				// Last camera position from view()
float lastCameraPosY;

vector<GLuint> IDs;                 // array with all images IDs

string fontName = "arial.ttf";      // Name of default font



// Lib states

bool waiting = false;               // state of waitning for keyboard event

bool inited = false;                // state of lib initialization

bool released = true;               // state of resorces realease

bool doublebuffered = true;        // state of double buffering (it needs to be set before initialization)



// Function pointers

void (*userMouseCallback)    (int x, int y, MouseButton mouseKey, InputAction mouseAction);
void (*userKeyboardCallback) (KeyboardKey keyboardKey, InputAction keyboardAction);


// Error reporting ( ends program)
void error(string msg)
{
  MsgBox(msg.data(),"LIBRARY ERROR :(");

  end();
}

// Error reporting (ends program)
void error(char * msg)
{
  MsgBox( msg, "LIBRARY ERROR :(" );

  end();
}

// Error reporting ( ends program)
void error(char * msg , string s)
{
   string m = msg;

   m += s;

   MsgBox(m.data() , "LIBRARY ERROR :(");

   end();
}

// Error callback for GLFW
void error(int code, const char * msg)
{
   string m = msg;

   m += " code : " + to_string(code);

   MsgBox(m.data() , "LIBRARY ERROR :(");

   end();
}

// Throws msgbox with error
void errorMsg(char * msg)
{
  MsgBox( msg, "USER DEFINED ERROR :(" );
}

// Throws msgbox with error
void errorMsg(string msg)
{
  MsgBox( msg.data(), "LIBRARY ERROR :(" );
}

// Throws msgbox with error and ends program
void errorCritical(char * msg)
{
  MsgBox( msg, "USER DEFINED ERROR :(" );

  exit(0);
}



// Default keyboard callback , calling user callback
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	KeyboardKey keyPressed = (KeyboardKey)key;
	InputAction keyAction = (InputAction)action;

	if (userKeyboardCallback != NULL)
		userKeyboardCallback(keyPressed, keyAction);

    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
    end();

	if(glfwWindowShouldClose(window))
	end();
}

// Default mouse callback , calling user callback
void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	MouseButton mouseButton = (MouseButton)button;
	InputAction mouseAction = (InputAction)action;

	if (userMouseCallback != NULL)
		userMouseCallback((int)xpos,(int)ypos, mouseButton, mouseAction);

}

// Waiting state keyboard callback
void waitingKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    waiting = false;

	if(glfwWindowShouldClose(window))
	end();
}


// atexit function , it checks for realeasing resorces
void atEnd()
{
	if( released == false )
	error("Memory is not released. Check if you used end().");
}

// Initialization of graphic window
void initGL(int w , int h)                                                      
{
	// First graphic window

	glfwSetErrorCallback(error);                                                // Callback for GLFW errors

	int result = glfwInit();

	if(result == GL_FALSE )                                                     // Checking
	error("Cannot init GLFW");


	if(!doublebuffered)
	glfwWindowHint( GLFW_DOUBLEBUFFER,GL_FALSE );                               // Turning off doublebuffering


    window = glfwCreateWindow( w , h , "SimpleGL", NULL , NULL );               // Creating window

	
	if(window == NULL)                                                          // Checking
	{
		
		int major, minor, rev;                                                  // Trying with other OGL version

        glfwGetVersion(&major, &minor, &rev);                                   // Get OpenGL version

	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);                      // Set that version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);


		window = glfwCreateWindow( w , h , "SimpleGL", NULL , NULL );           // Again window creation


		if(window == NULL)                                                      // Checking again
	    {
	       error("Cannot create window");                                         // Nothing will help now , throw error 
		}
	}

	inited = true;


	window_width = w;
	window_height = h;


    glfwMakeContextCurrent(window);	                                            // Choosing active context


	glfwSetKeyCallback(window, keyboardCallback);								// Setting up input callbacks
	glfwSetMouseButtonCallback(window, mouseCallback);

	// Now OpenGL


	glViewport(0,0,w,h);						                                // Setting viewport

	view(0, w, h, 0);

	glClearColor(0,0,0,0);                                            	        // default clear color

	glClear( GL_COLOR_BUFFER_BIT );                                             // first clearing

	glEnable(GL_TEXTURE_2D);                                                    // texturing

	glDisable(GL_LIGHTING);														// There's no need of lighting

    glEnable( GL_BLEND );	                                                	// blending

	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );                        // blending func

	glEnable(GL_DEPTH_TEST);                                                    // teting for depth

	glDepthFunc(GL_LEQUAL);                                                     // depth func

	glDepthRange(0.0f, 1.0f);                                               	// Range of depth

	glClearDepth(1.0f);                                                         // clearing depth value

	glEnable ( GL_ALPHA_TEST ) ;                                                // Testing for alpha component(RGBA)

	glAlphaFunc ( GL_GREATER, 0.1 ) ;                                           // Alpha func

	glPointSize(1);                                                           	// Default point size


	// Next loading font


	font = new FTGLPixmapFont(fontName.data());                                 // loading deafault font

	if(font->Error())                                                           // Checking
    error("FTGL cannot load font",fontName);

	font->FaceSize(fontSize);													// Font size

	font->UseDisplayList(true);                                                 // Display list are really okay


	// Are they any errors yet ?


	GLenum glError;

    glError = glGetError();

    if (glError != GL_NO_ERROR)
	error(glError,"OpenGL error");


	// At the end caring for resorces releasing

	released = false;

	clear();

	atexit(atEnd);
}

// Releasing resources
void end()
{
   if(font != NULL)
   delete font;

   font = NULL;

   if(window != NULL)
   glfwDestroyWindow(window);

   window = NULL;

   glfwTerminate();

   for(int i=0;i<IDs.size();i++)
   glDeleteTextures( 1, &IDs[i] );

   IDs.clear();

   released = true;

   exit(0);
}

// Sleeping thread ( time in miliseconds )
void sleep(int miliseconds)
{
	std::chrono::milliseconds dura( miliseconds );
    std::this_thread::sleep_for( dura );
}

// Pause till any key is pressed
void wait()
{
	waiting = true;

	glfwSetKeyCallback(window, waitingKeyboardCallback);

	while(waiting)
	{
	  glfwWaitEvents();
	}

	glfwSetKeyCallback(window, keyboardCallback);
}

// Set color used to clear the screen with clear()
void setClearColor(double r , double g , double b)
{
   glClearColor(r/255,g/255,b/255,0);
}

// Set color used to clear the screen with clear()
void setClearColor(ColorRGB color)
{
	glClearColor((float)color.r / 255, (float)color.g / 255, (float)color.b / 255, 0);
}

// Sets point size
void setPointSize(float size)
{
  glPointSize(size);
}

// Loading font from file
void setFont(char * name)
{
  if(inited == false)															// If program wasnt initialized
  {
     fontName = name;															// Just change font name
	 return;
  }

  FTGLPixmapFont * newfont = new FTGLPixmapFont(name);							// Loading new font

  if(newfont->Error())															// Checking 
  {
	delete newfont;																// If something went wrong
    MsgBox("FTGL cannot load font","ERROR");
	return;
  }

  fontName = name;

  newfont->FaceSize(fontSize);

  newfont->UseDisplayList(true);												// Use font display list

  delete font;																	// Delete old font

  font = newfont;																// Swap pointer to font
}

// Setting font size
void setFontSize(int size)
{
  fontSize = size;

  font->FaceSize(fontSize);

  font->UseDisplayList(true); 
}

// Setting double buffered mode(it needs to be set before initialization)
void setDoubleBuffered(bool state)
{
	if(inited == false)
	doublebuffered = state;
	else
	error("Double buffering needs to be set before initialization");
}

// Time from program start in miliseconds
double getTime()
{
	return glfwGetTime()*1000;
}


// Swaping buffers , clearing screen and checking for events
void checkEvents()
{
	glfwPollEvents();

	if (glfwWindowShouldClose(window))
		end();
}

// Setting Mouse Callback
void setMouseCallback(void(*mouseCallback)(int x, int y, MouseButton button, InputAction action))
{
	userMouseCallback = mouseCallback;
}

// Setting Keyboard Callback
void setKeyboardCallback(void(*keyboardCallback)(KeyboardKey key, InputAction action))
{
	userKeyboardCallback = keyboardCallback;
}

// Returns state of key
InputAction getKeyState(KeyboardKey key)
{
	InputAction state = (InputAction)glfwGetKey(window, (int)key);
	return state;
}

// Returns by reference current position of coursor
void getMousePosition(int & x, int & y)
{
	double xpos, ypos;

	glfwGetCursorPos(window, &xpos, &ypos);

	x = (int)xpos;
	y = (int)ypos;
}


// Sets view region to given coordinates
void view(float left , float right , float top , float bottom)
{
	float posX = (right + left) / 2.0f;
	float posY = (top + bottom) / 2.0f;

	lastCameraPosX = posX;
	lastCameraPosY = posY;

    glMatrixMode(GL_PROJECTION);                                                // projection matrix is identity
	glLoadIdentity();

	glOrtho(left, right, bottom, top, 1, -layers - 1);                          // Projection region

	glMatrixMode(GL_MODELVIEW);                                                 // model matrix is identity
	glLoadIdentity();	
}

// Rotate view , angle in degrees
void viewRotate(float angle)
{
	glMatrixMode(GL_PROJECTION);

	glTranslatef(lastCameraPosX, lastCameraPosY, 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-lastCameraPosX, -lastCameraPosY, 0);

	glMatrixMode(GL_MODELVIEW);
}

// Select current layer
void selectLayer(int layer)
{
  if(layer < 1 || layer > layers)
  {
    errorMsg("Wrong layer selected");
    return;
  }

 currentlayer = layer;
}


// Point ( size is set by setPointSize() )
void point(float x , float y)
{
	glBegin(GL_POINTS);

	glVertex3f(x,y,currentlayer);

	glEnd();

	if(doublebuffered == false)
	glFlush();
}

// Line between two points
void line(float x1 , float y1 , float x2 , float y2)
{
	glBegin(GL_LINES);

	glVertex3f(x1,y1,currentlayer);
	glVertex3f(x2,y2,currentlayer);

	glEnd();

	if(doublebuffered == false)
	glFlush();
}

// Circle in given point with given radius
void circle(float cx , float cy , float r)
{
	float vertNum = floor(10.0f * sqrtf(r));           // Counting vertices

	float theta = 2 * PI / vertNum ;                   // Angle between vertices

	float cosinus = cosf(theta);                       // Caching trig functions for theta
	float sinus   = sinf(theta);

	float x = r;                                       // Radius vector ( 0 degrees )
	float y = 0; 

	float x2;                                          // temp vector
	float y2;
    

	glBegin(GL_LINE_LOOP);                             // Drawing

	for(int i=0;i<vertNum;i++) 
	{ 
		glVertex3f(x + cx, y + cy,currentlayer);       // Send vertex to GPU
        

		x2 = cosinus * x  -   sinus * y;               // Matrix rotation of radius vector to temp
		y2 = sinus   * x  + cosinus * y;


		x = x2;                                        // From temp back to radius vector
		y = y2;
	} 
	glEnd(); 

	if(doublebuffered == false)
	glFlush();
}

// Polygon ( array of x , array of y , number of vertices)
void polygon( float * x , float * y , int n)
{
	glBegin(GL_POLYGON);

	for(int i=0;i<n;i++) 
	{ 
		glVertex3d(x[i],y[i],currentlayer);
	} 

	glEnd(); 

	if(doublebuffered == false)
	glFlush();
}

// Drawing text in given place
void text(float x , float y , char * t)
{
  glRasterPos3d(x,y,currentlayer - 0.1);
  font->Render(t);

  if(doublebuffered == false)
  glFlush();
}

// Drawing 2D rgb buffer ( x,y -> left down corner; width,height -> dimmensions; buff_w,buff_h -> buffer dimmensions; buffer must be unsigned byte)
void rgb_buffer(float x, float y, float width, float height, int buff_w, int buff_h, void * buffer)
{
	GLuint texture_id;

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,buff_w,buff_h,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);

	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(x, y, currentlayer);

	glTexCoord2f(1, 0);
	glVertex3f(x + width, y, currentlayer);

	glTexCoord2f(1, 1);
	glVertex3f(x + width, y +  height, currentlayer);

	glTexCoord2f(0, 1);
	glVertex3f(x, y + height, currentlayer);

	glEnd();

	glDeleteTextures(1, &texture_id);
}

// Clearing screnn with ClearColor
void clear()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

// Sets RGB color ( 0 - 255 )
void setColor(int r , int g , int b)
{
  glColor3ub(r,g,b);
}

// Sets RGB color
void setColor(ColorRGB color)
{
	glColor3ub(color.r, color.g, color.b);
}

// Sets gray color ( 0 - 255 )
void setGray(int value)
{
  glColor3ub(value,value,value);
}

// Swaping buffers , clearing screen
void swap()
{
	if(doublebuffered == false)
	error("Cannot swap without double buffering");

	glfwSwapBuffers(window);

	clear();
}


// Loading image from file and returning its ID
int loadImage(char * path)
{
	if (inited == false)
	{
		error("Loading images is not possible without lib initialization");
		return - 1;
	}

	int ID;

		ID = SOIL_load_OGL_texture											 // Loading texture and saving ID
	(
	path,
	SOIL_LOAD_RGBA ,
	SOIL_CREATE_NEW_ID,
	SOIL_FLAG_INVERT_Y
	);

	if (ID == 0)
	{
		error("Texture is not loaded");
		return 0;
	}


	glBindTexture(GL_TEXTURE_2D, ID);                                       // Texture filtering

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glBindTexture( GL_TEXTURE_2D, NULL ); 



	IDs.push_back(ID);

	return ID;
}

// Drawing image with given ID where x,y are coordinates of left bottom vertex
void drawImage(int ID , float x , float y , float width , float height)
{
	glBindTexture(GL_TEXTURE_2D, ID);						// Wybieramy teksture 

	glColor3f(1.0, 1.0, 1.0);								// Color modification ( 1.0 1.0 1.0 is texture color)

	glBegin(GL_QUADS);                                      // Drawing

	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, currentlayer);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, currentlayer);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, currentlayer);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, currentlayer);

	glEnd();

   glBindTexture( GL_TEXTURE_2D, NULL );

   if(doublebuffered == false)
   glFlush();
}

// Drawing image with given ID where x,y are coordinates of left bottom vertex and rotation is in degrees
void drawImage(int ID, float x, float y, float width, float height, int rotation)
{
	glBindTexture(GL_TEXTURE_2D, ID);						// Wybieramy teksture 

	glColor3f(1.0, 1.0, 1.0);								// Color modification ( 1.0 1.0 1.0 is texture color)

	if (rotation != 0)										// Rotation matrix
	{
		glPushMatrix();

		glTranslatef(x + width/2, y + height/2, 0);
		glRotatef((float)rotation, 0.0f, 0.0f, 1.0f);
		glTranslatef(-(x + width / 2), -(y + height / 2), 0);
	}

	glBegin(GL_QUADS);										// Drawing

	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, currentlayer);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, currentlayer);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, currentlayer);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, currentlayer);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);

	if (rotation != 0)
		glPopMatrix();

	if (doublebuffered == false)
		glFlush();
}

// Drawing image with given ID where x,y are coordinates of center of image
void drawImageCentered(int ID, float x, float y, float width, float height)
{
	glBindTexture(GL_TEXTURE_2D, ID);                        // Binding texture 

	glColor3f(1.0, 1.0, 1.0);								 // Color modification ( 1.0 1.0 1.0 is texture color)

	float hw = width / 2;
	float hh = height / 2;

	glBegin(GL_QUADS);                                       // Drawing

	glTexCoord2f(0.0f, 0.0f); glVertex3f(x - hw, y - hh, currentlayer);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + hw, y - hh, currentlayer);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + hw, y + hh, currentlayer);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x - hw, y + hh, currentlayer);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);

	if (doublebuffered == false)
		glFlush();
}

// Drawing image with given ID where x,y are coordinates of center of image and rotation is in degrees
void drawImageCentered(int ID, float x, float y, float width, float height, int rotation)
{
	glBindTexture(GL_TEXTURE_2D, ID);                        // Binding texture

	glColor3f(1.0, 1.0, 1.0);								 // Color modification ( 1.0 1.0 1.0 is texture color)

	float hw = width / 2;
	float hh = height / 2;

	if (rotation != 0)                                        // Rotation matrix
	{
		glPushMatrix();

		glTranslatef(x, y, 0);
		glRotatef((float)rotation, 0.0f, 0.0f, 1.0f);
		glTranslatef(-x, -y, 0);
	}

	glBegin(GL_QUADS);                                       // Drawing

	glTexCoord2f(0.0f, 0.0f); glVertex3f(x - hw, y - hh, currentlayer);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + hw, y - hh, currentlayer);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + hw, y + hh, currentlayer);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x - hw, y + hh, currentlayer);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);

	if (rotation != 0)
	glPopMatrix();

	if (doublebuffered == false)
	glFlush();
}

// Changes all pixels with given color to transparent
void keyColor(int ID , int r , int g , int b)
{
  int pixRGBA[4];                                                                         // var for getting pixel

  int w;                                                                                  // teture dimmensions
  int h;

  glBindTexture(GL_TEXTURE_2D, ID);

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0 , GL_TEXTURE_WIDTH , (GLint*)&w);             // Getting dimmensions
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0 , GL_TEXTURE_HEIGHT, (GLint*)&h);

  GLuint * pixels = new GLuint[ w * h ];                                                  // Array for texture

  glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );                   // Loading

  for(int i=0;i<w*h;i++)
  {
	 GLubyte* col = (GLubyte*)&pixels[i];                                                 // Casting pixel to RGBA

     pixRGBA[0] = col[ 0 ];
     pixRGBA[1] = col[ 1 ];
     pixRGBA[2] = col[ 2 ];
     pixRGBA[3] = col[ 3 ];

	 if(pixRGBA[0]== r && pixRGBA[1] == g && pixRGBA[2] == b)                             // If this is key color
	 {
	   pixels[i] = 0;
	 }
  }

  glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels );     // Sedning back to GPU

  delete[] pixels;                                                                        // Deleting array

  glBindTexture( GL_TEXTURE_2D, NULL );                                                   // Unbinding texture
}

// Changes all pixels with given color to transparent
void keyColor(int ID, ColorRGB color)
{
	keyColor(ID, color.r, color.g, color.b);
}

// Saving screeshot with given name in .bmp format
void screenshot(char * filename)
{
    int err = SOIL_save_screenshot
	(
		"screen.bmp",
		SOIL_SAVE_TYPE_BMP,
		0, 0, window_width, window_height
	);

	if(err == 0)
	{
		string s = "SOIL library error : ";

		s += SOIL_last_result();

	    errorMsg(s);
	}
}