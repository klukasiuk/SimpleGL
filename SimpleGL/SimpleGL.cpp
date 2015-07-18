#include "SimpleGL.h"

#define PI       3.14159265358979323846       

// Biblioteka standardowa ( chrono i thread -> C++11 )

#include <math.h>                   // funckje matematyczne
#include <vector>                   // Dynamiczna tablica
#include <chrono>                   // funkcja Sleep
#include <thread>                   // funkcja Sleep
#include <string>                   // Pomocna w napisach( s1 + s2 itd. )

#include <fstream>


// Dodatkowe biblioteki do OpenGL

#include <FTGL/ftgl.h>              // rysowanie tekstu
#include <SOIL.h>                   // wczytywanie tekstur
#include <glfw3.h>                  // obs�uga okna


// Warstwa abstrakcji mi�dzy windows.h(czyste z�o) a nasz� przestrzeni� nazw
// U�ywam message boxa do raportowania b��d�w
#include "msgbox.h"


// Wczytuje nazwy

using std::string;
using std::to_string;
using std::vector;


// Zmienne globalne

GLFWwindow * window = NULL;         // Uchwyt na okno
FTGLPixmapFont * font = NULL;       // Czcionka

int window_height;                  // wymiary okna
int window_width;

bool waiting = false;               // stan oczekiwania na event klawiatry

bool released = true;               // flaga zwolnienie zasob�w ( sprawdzana atexit )

vector<GLuint> IDs;                 // wektor z ID tekstur

string fontName = "arial.ttf";      // Nazwa domy�lnej czcionki ( dost�pne jeszcze calibri)




// Raportowanie b��du ( ko�czy dzia�anie programu)
void error(string msg)
{
  MsgBox(msg.data(),"LIBRARY ERROR :(");

  end();
}

// Raportowanie b��du ( ko�czy dzia�anie programu)
void error(char * msg)
{
  MsgBox( msg, "LIBRARY ERROR :(" );

  end();
}

// Raportowanie b��du ( ko�czy dzia�anie programu)
void error(char * msg , string s)
{
   string m = msg;

   m += s;

   MsgBox(m.data() , "LIBRARY ERROR :(");

   end();
}

// Error callback dla GLFW
void error(int code, const char * msg)
{
   string m = msg;

   m += " code : " + to_string(code);

   MsgBox(m.data() , "LIBRARY ERROR :(");

   end();
}

// Wyrzuca message boxa z b��dem
void errorMsg(char * msg)
{
  MsgBox( msg, "USER DEFINED ERROR :(" );
}

//Wyrzuca message boxa nast�pnie zwalnia pami�� i ko�czy program
void errorCritical(char * msg)
{
  MsgBox( msg, "USER DEFINED ERROR :(" );

  exit(0);
}


void atEnd()
{
	if( released == false )
	error(" Nie zwolniono pami�ci ");
}


// Inicjalizacja okna graficznego
void initGL(int w , int h)                                                      
{
	// Najpierw samo okno


	glfwSetErrorCallback(error);                                               // Callback dla b��d�w GLFW

	int result = glfwInit();                                                    // Inicjalizacja GLFW

	if(result == GL_FALSE )                                                     // Sprawdzam inicjalizacje
	error("Nie zainicjalizowano glfw");


	int major, minor, rev;

    glfwGetVersion(&major, &minor, &rev);                                       // Pobieram wersje OpenGL

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);                          // Ustawiam j� jako preferowan�
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);


	glfwWindowHint( GLFW_DOUBLEBUFFER,GL_FALSE );                               // Wy��czam podw�jne buforowanie


    window = glfwCreateWindow( w , h , "OpenFrame", NULL , NULL );              // Tworzenie okna

	if(window == NULL)                                                          // Sprawdzam utworzone okno
	error("Nie utworzono okna");


    glfwMakeContextCurrent(window);	                                            // Wybieram kontekst


	// Teraz OpenGL


	glViewport(0,0,w,h);						                                // Wybieram obszar wyswietlania

	glMatrixMode(GL_PROJECTION);                                                // Macierz projekcji = jednsotkowa
	glLoadIdentity();

	glOrtho(0,w,0,h,-1,1);                                                      // Obszar projekcji

	glMatrixMode(GL_MODELVIEW);                                                 // Macierz modelowania = jednsotkowa
	glLoadIdentity();	

	glClearColor(1,1,1,0);                                            	        // Kolor czyszczenia ekranu

	glClear( GL_COLOR_BUFFER_BIT );                                             // Czyszcz� wst�pnie ekran

	glEnable(GL_TEXTURE_2D);                                                    // W��czam teksturowaie

    glEnable( GL_BLEND );	                                                	// Mieszanie kolor�w

	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );                        //Funkcja mieszania kolor�w

	glPointSize(1);                                                           	// Wielko�� punkt�w


	// Teraz �aduj� czcionk�


	font = new FTGLPixmapFont(fontName.data());                                 // �aduje domy�ln� czcionk�

	if(font->Error())                                                           // Sprawdzam czy si� uda�o
    error("FTGL nie za�adowa� czcionki",fontName);

	font->FaceSize(12);                                                         // Wielko�� czcionki

	font->UseDisplayList(true);                                                 // U�ywam list wy�wietlania


	// Sprawdzam b��dy OpenGL


	GLenum glError;

    glError = glGetError();

    if (glError != GL_NO_ERROR)
	error(glError,"Blad OpenGL");

	// Na koniec w trosce o zwolnienie zasob�w

	released = false;

	atexit(atEnd);
}

// Zwolnienie zasob�w
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

// U�pienie w�tku 
void sleep(int miliseconds)
{
	std::chrono::milliseconds dura( miliseconds );
    std::this_thread::sleep_for( dura );
}

// Callback dla klawiatury podczas oczekiwania na wci�niecia klawisza
void waiting_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    waiting = false;
}

// Pauza do naci�ni�cia klawisza
void wait()
{
	waiting = true;

	glfwSetKeyCallback(window, waiting_callback);

	while(waiting)
	{
	  glfwWaitEvents();

	  if(glfwWindowShouldClose(window))
	  end();
	}
}



// Odcinek mi�dzy dwoma punktami
void line(float x1 , float y1 , float x2 , float y2)
{
	glBegin(GL_LINES);

	glVertex2f(x1,y1);
	glVertex2f(x2,y2);

	glEnd();

	glFlush();
}

// Ko�o o danym �rodku i promieniu
void circle(float cx , float cy , float r)
{
	float vertNum = floor(10.0f * sqrtf(r));           // Licz� liczb� wierzcho�k�w (pod�oga bo musi by� ca�kowita)

	float theta = 2 * PI / vertNum ;                   // Licz� k�t mi�dzy wiercho�kami

	float cosinus = cosf(theta);                       // Licz� funkcje trygonometryczne dla theta
	float sinus   = sinf(theta);

	float x = r;                                       // Wektor od �rodka do okr�gu ( dla 0 stopni )
	float y = 0; 

	float x2;                                          // Wektor pomocniczy
	float y2;
    

	glBegin(GL_LINE_LOOP);                             // Rysowanie

	for(int i=0;i<vertNum;i++) 
	{ 
		glVertex2f(x + cx, y + cy);                    // Wysy�am wierzcho�ek
        

		x2 = cosinus * x  -   sinus * y;               // Obr�t macierz�
		y2 = sinus   * x  + cosinus * y;


		x = x2;                                        // Zapisuje wsp�rz�dne po transformacji
		y = y2;

	} 
	glEnd(); 

	glFlush();
}

// Rysuje tekst w danym miejscu
void text(int x , int y , char * t)
{
  glRasterPos2i(x,y);
  font->Render(t);

  glFlush();
}

// Czyszczenie ekranu
void clear()
{
   glClear( GL_COLOR_BUFFER_BIT );
}

// Ustawienie koloru RGB ( 0 - 255 )
void setColor(int r , int g , int b)
{
  glColor3ub(r,g,b);
}



// Wczytuje plik do tekstury i zwraca ID
int loadImage(char * path)
{
  int ID;

  ID = SOIL_load_OGL_texture     // Wczytujemy teskture , id zapisujemy
  (
  path,
  SOIL_LOAD_RGBA ,
  SOIL_CREATE_NEW_ID,
  SOIL_FLAG_INVERT_Y
  );

  if(ID == 0)
  error("Nie wczytano tekstury");


  glBindTexture(GL_TEXTURE_2D, ID);                                       // Ustawiam filtrowanie tekstury 

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  glBindTexture( GL_TEXTURE_2D, NULL ); 



  IDs.push_back(ID);

  return ID;
}

// Rysuje teksture o ID w danym miejscu ( x , y , szeroko�� , wysoko��) x,y lewego dolnego wierzcho�ka
void drawImage(int ID , float x , float y , float width , float height)
{
   glBindTexture(GL_TEXTURE_2D, ID);                        // Wybieramy teksture 

   glColor3f(1.0, 1.0, 1.0);                           // Modyfikacja koloru

   glBegin(GL_QUADS);                                       // Zaczynamy rysowanie

   glTexCoord2f(0.0f, 0.0f); glVertex2f(x         , y           );
   glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width , y           );
   glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width , y + height  );
   glTexCoord2f(0.0f, 1.0f); glVertex2f(x         , y + height  );

   glEnd();

   glBindTexture( GL_TEXTURE_2D, NULL );

   glFlush();
}

// Ustawia podany kolor na zupe�nie przezroczyste t�o
void keyColor(int ID , int r , int g , int b)
{

  int pixRGBA[4];                                                                         // Zmienna na pobrany pixel

  int w;                                                                                  // Wymiary tekstury
  int h;

  glBindTexture(GL_TEXTURE_2D, ID);                                                       // Binduje teksture  

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0 , GL_TEXTURE_WIDTH , (GLint*)&w);             // Pobieram wymiary
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0 , GL_TEXTURE_HEIGHT, (GLint*)&h);

  GLuint * pixels = new GLuint[ w * h ];                                                  // Tworz� tablic� na teksture

  glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );                   // Wczytuje

  for(int i=0;i<w*h;i++)
  {
	 GLubyte* col = (GLubyte*)&pixels[i];                                                 // Dekoduje pobrany piksel do RGBA

     pixRGBA[0] = col[ 0 ];
     pixRGBA[1] = col[ 1 ];
     pixRGBA[2] = col[ 2 ];
     pixRGBA[3] = col[ 3 ];

	 if(pixRGBA[0]== r && pixRGBA[1] == g && pixRGBA[2] == b)                             // Je�li kolor si� zgadza
	 {
	   pixels[i] = 0;
	 }
  }

  glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels );     // Wysy�am spowrotem do GPU

  delete[] pixels;                                                                        // Usuwam wczytane piksele

  glBindTexture( GL_TEXTURE_2D, NULL );                                                   // Odpinam teksture
}