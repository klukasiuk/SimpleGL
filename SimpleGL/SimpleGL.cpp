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
#include <glfw3.h>                  // obs³uga okna


// Warstwa abstrakcji miêdzy windows.h(czyste z³o) a nasz¹ przestrzeni¹ nazw
// U¿ywam message boxa do raportowania b³êdów
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

int fontSize = 12;                  // Domyœlna wielkoœæ czcionki

float layers = 3.0;                 // Liczba warstw

float currentlayer = 1.0;           // Obecna warstwa      

vector<GLuint> IDs;                 // wektor z ID tekstur

string fontName = "arial.ttf";      // Nazwa domyœlnej czcionki ( dostêpne jeszcze calibri)



// Stany biblioteki

bool waiting = false;               // stan oczekiwania na event klawiatry

bool inited = false;                // stan zainicjowania biblioteki

bool released = true;               // stan zwolnienie zasobów ( sprawdzany atexit )

bool doublebuffered = false;        // stan podwójnego buforowania




// Raportowanie b³êdu ( koñczy dzia³anie programu)
void error(string msg)
{
  MsgBox(msg.data(),"LIBRARY ERROR :(");

  end();
}

// Raportowanie b³êdu ( koñczy dzia³anie programu)
void error(char * msg)
{
  MsgBox( msg, "LIBRARY ERROR :(" );

  end();
}

// Raportowanie b³êdu ( koñczy dzia³anie programu)
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

// Wyrzuca message boxa z b³êdem
void errorMsg(char * msg)
{
  MsgBox( msg, "USER DEFINED ERROR :(" );
}

// Wyrzuca message boxa z b³êdem
void errorMsg(string msg)
{
  MsgBox( msg.data(), "LIBRARY ERROR :(" );
}

//Wyrzuca message boxa nastêpnie zwalnia pamiêæ i koñczy program
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

// Callback dla klawiatury podczas oczekiwania na wciœniecia klawisza
void waitingCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    waiting = false;

	if(glfwWindowShouldClose(window))
	end();
}



// Funkcja atexit , pilnuje zwolnienia zasobów
void atEnd()
{
	if( released == false )
	error(" Nie zwolniono pamiêci . Upewnij siê ¿e u¿ywasz funkcji end() do zakoñczenie programu .");
}

// Inicjalizacja okna graficznego
void initGL(int w , int h)                                                      
{
	// Najpierw samo okno


	glfwSetErrorCallback(error);                                                // Callback dla b³êdów GLFW

	int result = glfwInit();                                                    // Inicjalizacja GLFW

	if(result == GL_FALSE )                                                     // Sprawdzam inicjalizacje
	error("Nie zainicjalizowano glfw");


	if(!doublebuffered)
	glfwWindowHint( GLFW_DOUBLEBUFFER,GL_FALSE );                               // Wy³¹czam podwójne buforowanie


    window = glfwCreateWindow( w , h , "SimpleGL", NULL , NULL );               // Tworzenie okna

	
	if(window == NULL)                                                          // Sprawdzam utworzone okno
	{
		
		int major, minor, rev;                                                  // Próbuje utworzyæ kontekst z inn¹ wersj¹ OGL

        glfwGetVersion(&major, &minor, &rev);                                   // Pobieram wersje OpenGL

	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);                      // Ustawiam j¹ jako preferowan¹
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);


		window = glfwCreateWindow( w , h , "SimpleGL", NULL , NULL );           // Znowu tworzenie okna


		if(window == NULL)                                                      // Sprawdzam czy tym razem siê uda³o
	    {
	       error("Nie utworzono okna");                                         // Nic ju¿ nie pomo¿e , wywalam b³¹d
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

	glClear( GL_COLOR_BUFFER_BIT );                                             // Czyszczê wstêpnie ekran

	glEnable(GL_TEXTURE_2D);                                                    // W³¹czam teksturowaie

    glEnable( GL_BLEND );	                                                	// Mieszanie kolorów

	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );                        //Funkcja mieszania kolorów

	glEnable(GL_DEPTH_TEST);                                                    // Testy buforu g³ebokoœci

	glDepthFunc(GL_LEQUAL);                                                     // Funkcja buforu g³ebokoœci

	glDepthRange(0.0f, 1.0f);                                               	// Zakres Depth Buforu

	glClearDepth(1.0f);                                                         // Wartoœæ czyszczenie depth buforu

	glEnable ( GL_ALPHA_TEST ) ;                                                // Alfa testy

	glAlphaFunc ( GL_GREATER, 0.1 ) ;                                           // Funkcja alfa

	glPointSize(1);                                                           	// Wielkoœæ punktów


	// Teraz ³adujê czcionkê


	font = new FTGLPixmapFont(fontName.data());                                 // £aduje domyœln¹ czcionkê

	if(font->Error())                                                           // Sprawdzam czy siê uda³o
    error("FTGL nie za³adowa³ czcionki",fontName);

	font->FaceSize(fontSize);                                                         // Wielkoœæ czcionki

	font->UseDisplayList(true);                                                 // U¿ywam list wyœwietlania


	// Sprawdzam b³êdy OpenGL


	GLenum glError;

    glError = glGetError();

    if (glError != GL_NO_ERROR)
	error(glError,"Blad OpenGL");

	// Na koniec w trosce o zwolnienie zasobów

	released = false;

	clear();

	atexit(atEnd);
}

// Zwolnienie zasobów
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

// Uœpienie w¹tku 
void sleep(int miliseconds)
{
	std::chrono::milliseconds dura( miliseconds );
    std::this_thread::sleep_for( dura );
}

// Pauza do naciœniêcia klawisza
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

// Ustawia wielkoœæ rysowanych punktów
void setPointSize(float size)
{
  glPointSize(size);
}

// Wczytuje czcionkê
void setFont(char * name)
{
  if(font == NULL)                                                              // Jeœli czcionka nie zosta³a jeszcze wczytana
  {
     fontName = name;                                                           // Zmienaiam nazwê czcionki
	 return;
  }

  FTGLPixmapFont * newfont = new FTGLPixmapFont(name);                           // Wczytuje now¹ czcionkê

  if(newfont->Error())                                                           // Sprawdzam czy siê uda³o
  {
	delete newfont;                                                              // Jeœli nie to usuwam zadeklarowan¹ pamiêæ
    MsgBox("FTGL nie móg³ za³adowaæ nowej czcionki ","ERROR");
	return;
  }

  newfont->FaceSize(fontSize);                                                   // Wielkoœæ czcionki

  newfont->UseDisplayList(true);                                                 // U¿ywam list wyœwietlania

  delete font;                                                                   // Usuwam star¹ czcionkê

  font = newfont;                                                                // Podmieniam wskaŸnik na now¹
}

// Ustawiam wielkoœæ czcionki
void setFontSize(int size)
{
  fontSize = size;

  font->FaceSize(fontSize);

  font->UseDisplayList(true); 
}

// Ustawia podwójne buforowanie
void setDoubleBuffered(bool state)
{
	if(inited == false)
	doublebuffered = state;
	else
	error("Podwójne buforowanie powinno byæ ustawione przed utworzeniem okna");
}


// Zwraca czas od pocz¹tku programu
double getTime()
{
	return glfwGetTime();
}



// Ustawia rzutowanie prostok¹tne w okreœlonym obszarze
void view(float left , float right , float top , float bottom)
{
    glMatrixMode(GL_PROJECTION);                                                // Macierz projekcji = jednsotkowa
	glLoadIdentity();

	glOrtho(left,right,bottom,top,1,layers);                                    // Obszar projekcji

	glMatrixMode(GL_MODELVIEW);                                                 // Macierz modelowania = jednsotkowa
	glLoadIdentity();	

}

// Wybiera warstwê
void selectLayer(int layer)
{
  if(layer < 1 || layer > layers)
  {
    errorMsg("Podany z³y numer warstwy");
    return;
  }

 currentlayer = layer;
}



// Punkt ( wielkoœc okreœle setPointSize)
void point(float x , float y)
{
	glBegin(GL_POINTS);

	glVertex3f(x,y,currentlayer);

	glEnd();

	if(doublebuffered == false)
	glFlush();
}

// Odcinek miêdzy dwoma punktami
void line(float x1 , float y1 , float x2 , float y2)
{
	glBegin(GL_LINES);

	glVertex3f(x1,y1,currentlayer);
	glVertex3f(x2,y2,currentlayer);

	glEnd();

	if(doublebuffered == false)
	glFlush();
}

// Ko³o o danym œrodku i promieniu
void circle(float cx , float cy , float r)
{
	float vertNum = floor(10.0f * sqrtf(r));           // Liczê liczbê wierzcho³ków (pod³oga bo musi byæ ca³kowita)

	float theta = 2 * PI / vertNum ;                   // Liczê k¹t miêdzy wiercho³kami

	float cosinus = cosf(theta);                       // Liczê funkcje trygonometryczne dla theta
	float sinus   = sinf(theta);

	float x = r;                                       // Wektor od œrodka do okrêgu ( dla 0 stopni )
	float y = 0; 

	float x2;                                          // Wektor pomocniczy
	float y2;
    

	glBegin(GL_LINE_LOOP);                             // Rysowanie

	for(int i=0;i<vertNum;i++) 
	{ 
		glVertex3f(x + cx, y + cy,currentlayer);       // Wysy³am wierzcho³ek
        

		x2 = cosinus * x  -   sinus * y;               // Obrót macierz¹
		y2 = sinus   * x  + cosinus * y;


		x = x2;                                        // Zapisuje wspó³rzêdne po transformacji
		y = y2;

	} 
	glEnd(); 

	if(doublebuffered == false)
	glFlush();
}

// Wielok¹t ( tablica x , tablica y , iloœæ wierzcho³ków)
void polygon( float * x , float * y , int n)
{
	glBegin(GL_POLYGON);                             // Rysowanie

	for(int i=0;i<n;i++) 
	{ 
		glVertex3d(x[i],y[i],currentlayer);       // Wysy³am wierzcho³ek
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
	error(" Nie da siê zamieniæ buforów bez podwójnego buforowania");

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

// Rysuje teksture o ID w danym miejscu ( x , y , szerokoœæ , wysokoœæ) x,y lewego dolnego wierzcho³ka
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

// Ustawia podany kolor na zupe³nie przezroczyste t³o
void keyColor(int ID , int r , int g , int b)
{

  int pixRGBA[4];                                                                         // Zmienna na pobrany pixel

  int w;                                                                                  // Wymiary tekstury
  int h;

  glBindTexture(GL_TEXTURE_2D, ID);                                                       // Binduje teksture  

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0 , GL_TEXTURE_WIDTH , (GLint*)&w);             // Pobieram wymiary
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0 , GL_TEXTURE_HEIGHT, (GLint*)&h);

  GLuint * pixels = new GLuint[ w * h ];                                                  // Tworzê tablicê na teksture

  glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );                   // Wczytuje

  for(int i=0;i<w*h;i++)
  {
	 GLubyte* col = (GLubyte*)&pixels[i];                                                 // Dekoduje pobrany piksel do RGBA

     pixRGBA[0] = col[ 0 ];
     pixRGBA[1] = col[ 1 ];
     pixRGBA[2] = col[ 2 ];
     pixRGBA[3] = col[ 3 ];

	 if(pixRGBA[0]== r && pixRGBA[1] == g && pixRGBA[2] == b)                             // Jeœli kolor siê zgadza
	 {
	   pixels[i] = 0;
	 }
  }

  glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels );     // Wysy³am spowrotem do GPU

  delete[] pixels;                                                                        // Usuwam wczytane piksele

  glBindTexture( GL_TEXTURE_2D, NULL );                                                   // Odpinam teksture
}

// Zapisuje zrzut ekranu pod podan¹ nazw¹ w formacie BMP
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
		string s = "B³¹d biblioteki SOIL : ";

		s += SOIL_last_result();

	    errorMsg(s);
	}
}