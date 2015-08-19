#include "SimpleGL.h"

// Makro definicje

#define PI       3.14159265358979323846       

// Biblioteka standardowa ( chrono i thread -> C++11 )

#include <math.h>                   // funckje matematyczne
#include <vector>                   // Dynamiczna tablica
#include <chrono>                   // funkcja Sleep
#include <thread>                   // funkcja Sleep
#include <string>                   // Pomocna w napisach( s1 + s2 itd. )


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

int fontSize = 12;                  // Domy�lna wielko�� czcionki

float layers = 3.0;                 // Liczba warstw

float currentlayer = 1.0;           // Obecna warstwa      

vector<GLuint> IDs;                 // wektor z ID tekstur

string fontName = "arial.ttf";      // Nazwa domy�lnej czcionki ( dost�pne jeszcze calibri)



// Stany biblioteki

bool waiting = false;               // stan oczekiwania na event klawiatry

bool inited = false;                // stan zainicjowania biblioteki

bool released = true;               // stan zwolnienie zasob�w ( sprawdzany atexit )

bool doublebuffered = false;        // stan podw�jnego buforowania




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

// Wyrzuca message boxa z b��dem
void errorMsg(string msg)
{
  MsgBox( msg.data(), "LIBRARY ERROR :(" );
}

//Wyrzuca message boxa nast�pnie zwalnia pami�� i ko�czy program
void errorCritical(char * msg)
{
  MsgBox( msg, "USER DEFINED ERROR :(" );

  exit(0);
}



// Standardowy callback klawiatury
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
    end();

	if(glfwWindowShouldClose(window))
	end();
}

// Callback dla klawiatury podczas oczekiwania na wci�niecia klawisza
void waitingCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    waiting = false;

	if(glfwWindowShouldClose(window))
	end();
}



// Funkcja atexit , pilnuje zwolnienia zasob�w
void atEnd()
{
	if( released == false )
	error(" Nie zwolniono pami�ci . Upewnij si� �e u�ywasz funkcji end() do zako�czenie programu .");
}

// Inicjalizacja okna graficznego
void initGL(int w , int h)                                                      
{
	// Najpierw samo okno


	glfwSetErrorCallback(error);                                                // Callback dla b��d�w GLFW

	int result = glfwInit();                                                    // Inicjalizacja GLFW

	if(result == GL_FALSE )                                                     // Sprawdzam inicjalizacje
	error("Nie zainicjalizowano glfw");


	if(!doublebuffered)
	glfwWindowHint( GLFW_DOUBLEBUFFER,GL_FALSE );                               // Wy��czam podw�jne buforowanie


    window = glfwCreateWindow( w , h , "SimpleGL", NULL , NULL );               // Tworzenie okna

	
	if(window == NULL)                                                          // Sprawdzam utworzone okno
	{
		
		int major, minor, rev;                                                  // Pr�buje utworzy� kontekst z inn� wersj� OGL

        glfwGetVersion(&major, &minor, &rev);                                   // Pobieram wersje OpenGL

	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);                      // Ustawiam j� jako preferowan�
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);


		window = glfwCreateWindow( w , h , "SimpleGL", NULL , NULL );           // Znowu tworzenie okna


		if(window == NULL)                                                      // Sprawdzam czy tym razem si� uda�o
	    {
	       error("Nie utworzono okna");                                         // Nic ju� nie pomo�e , wywalam b��d
		}
	}

	inited = true;


	window_width = w;
	window_height = h;


    glfwMakeContextCurrent(window);	                                            // Wybieram kontekst


	glfwSetKeyCallback(window,keyCallback);


	// Teraz OpenGL


	glViewport(0,0,w,h);						                                // Wybieram obszar wyswietlania

	glMatrixMode(GL_PROJECTION);                                                // Macierz projekcji = jednsotkowa
	glLoadIdentity();

	glOrtho(0,w,0,h,1,-layers-1);                                               // Obszar projekcji

	glMatrixMode(GL_MODELVIEW);                                                 // Macierz modelowania = jednsotkowa
	glLoadIdentity();	

	glClearColor(0,0,0,0);                                            	        // Kolor czyszczenia ekranu

	glClear( GL_COLOR_BUFFER_BIT );                                             // Czyszcz� wst�pnie ekran

	glEnable(GL_TEXTURE_2D);                                                    // W��czam teksturowaie

    glEnable( GL_BLEND );	                                                	// Mieszanie kolor�w

	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );                        //Funkcja mieszania kolor�w

	glEnable(GL_DEPTH_TEST);                                                    // Testy buforu g�eboko�ci

	glDepthFunc(GL_LEQUAL);                                                     // Funkcja buforu g�eboko�ci

	glDepthRange(0.0f, 1.0f);                                               	// Zakres Depth Buforu

	glClearDepth(1.0f);                                                         // Warto�� czyszczenie depth buforu

	glEnable ( GL_ALPHA_TEST ) ;                                                // Alfa testy

	glAlphaFunc ( GL_GREATER, 0.1 ) ;                                           // Funkcja alfa

	glPointSize(1);                                                           	// Wielko�� punkt�w


	// Teraz �aduj� czcionk�


	font = new FTGLPixmapFont(fontName.data());                                 // �aduje domy�ln� czcionk�

	if(font->Error())                                                           // Sprawdzam czy si� uda�o
    error("FTGL nie za�adowa� czcionki",fontName);

	font->FaceSize(fontSize);                                                         // Wielko�� czcionki

	font->UseDisplayList(true);                                                 // U�ywam list wy�wietlania


	// Sprawdzam b��dy OpenGL


	GLenum glError;

    glError = glGetError();

    if (glError != GL_NO_ERROR)
	error(glError,"Blad OpenGL");

	// Na koniec w trosce o zwolnienie zasob�w

	released = false;

	clear();

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

// Pauza do naci�ni�cia klawisza
void wait()
{
	waiting = true;

	glfwSetKeyCallback(window, waitingCallback);

	while(waiting)
	{
	  glfwWaitEvents();
	}
}

// Ustawia kolor czysczenia ekranu
void setClearColor(double r , double g , double b)
{
   glClearColor(r/255,g/255,b/255,0);
}

// Ustawia wielko�� rysowanych punkt�w
void setPointSize(float size)
{
  glPointSize(size);
}

// Wczytuje czcionk�
void setFont(char * name)
{
  if(font == NULL)                                                              // Je�li czcionka nie zosta�a jeszcze wczytana
  {
     fontName = name;                                                           // Zmienaiam nazw� czcionki
	 return;
  }

  FTGLPixmapFont * newfont = new FTGLPixmapFont(name);                           // Wczytuje now� czcionk�

  if(newfont->Error())                                                           // Sprawdzam czy si� uda�o
  {
	delete newfont;                                                              // Je�li nie to usuwam zadeklarowan� pami��
    MsgBox("FTGL nie m�g� za�adowa� nowej czcionki ","ERROR");
	return;
  }

  newfont->FaceSize(fontSize);                                                   // Wielko�� czcionki

  newfont->UseDisplayList(true);                                                 // U�ywam list wy�wietlania

  delete font;                                                                   // Usuwam star� czcionk�

  font = newfont;                                                                // Podmieniam wska�nik na now�
}

// Ustawiam wielko�� czcionki
void setFontSize(int size)
{
  fontSize = size;

  font->FaceSize(fontSize);

  font->UseDisplayList(true); 
}

// Ustawia podw�jne buforowanie
void setDoubleBuffered(bool state)
{
	if(inited == false)
	doublebuffered = state;
	else
	error("Podw�jne buforowanie powinno by� ustawione przed utworzeniem okna");
}


// Zwraca czas od pocz�tku programu
double getTime()
{
	return glfwGetTime();
}



// Ustawia rzutowanie prostok�tne w okre�lonym obszarze
void view(float left , float right , float top , float bottom)
{
    glMatrixMode(GL_PROJECTION);                                                // Macierz projekcji = jednsotkowa
	glLoadIdentity();

	glOrtho(left,right,bottom,top,1,layers);                                    // Obszar projekcji

	glMatrixMode(GL_MODELVIEW);                                                 // Macierz modelowania = jednsotkowa
	glLoadIdentity();	

}

// Wybiera warstw�
void selectLayer(int layer)
{
  if(layer < 1 || layer > layers)
  {
    errorMsg("Podany z�y numer warstwy");
    return;
  }

 currentlayer = layer;
}



// Punkt ( wielko�c okre�le setPointSize)
void point(float x , float y)
{
	glBegin(GL_POINTS);

	glVertex3f(x,y,currentlayer);

	glEnd();

	if(doublebuffered == false)
	glFlush();
}

// Odcinek mi�dzy dwoma punktami
void line(float x1 , float y1 , float x2 , float y2)
{
	glBegin(GL_LINES);

	glVertex3f(x1,y1,currentlayer);
	glVertex3f(x2,y2,currentlayer);

	glEnd();

	if(doublebuffered == false)
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
		glVertex3f(x + cx, y + cy,currentlayer);       // Wysy�am wierzcho�ek
        

		x2 = cosinus * x  -   sinus * y;               // Obr�t macierz�
		y2 = sinus   * x  + cosinus * y;


		x = x2;                                        // Zapisuje wsp�rz�dne po transformacji
		y = y2;

	} 
	glEnd(); 

	if(doublebuffered == false)
	glFlush();
}

// Wielok�t ( tablica x , tablica y , ilo�� wierzcho�k�w)
void polygon( float * x , float * y , int n)
{
	glBegin(GL_POLYGON);                             // Rysowanie

	for(int i=0;i<n;i++) 
	{ 
		glVertex3d(x[i],y[i],currentlayer);       // Wysy�am wierzcho�ek
	} 

	glEnd(); 

	if(doublebuffered == false)
	glFlush();
}

// Rysuje tekst w danym miejscu
void text(float x , float y , char * t)
{
  glRasterPos3d(x,y,currentlayer - 0.1);
  font->Render(t);

  if(doublebuffered == false)
  glFlush();
}

// Czyszczenie ekranu
void clear()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

// Ustawienie koloru RGB ( 0 - 255 )
void setColor(int r , int g , int b)
{
  glColor3ub(r,g,b);
}

// Ustawia szary kolor ( 0 - 255 )
void setGray(int value)
{
  glColor3ub(value,value,value);
}

// Zamienia bufory okna , sprawdza eventy
void swap()
{
	if(doublebuffered == false)
	error(" Nie da si� zamieni� bufor�w bez podw�jnego buforowania");

	glfwSwapBuffers(window);

	checkEvents();

	clear();
}

// Sprawdza eventy
void checkEvents()
{
  glfwPollEvents();

  if(glfwWindowShouldClose(window))
  end();
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

   if(doublebuffered == false)
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

// Zapisuje zrzut ekranu pod podan� nazw� w formacie BMP
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
		string s = "B��d biblioteki SOIL : ";

		s += SOIL_last_result();

	    errorMsg(s);
	}
}