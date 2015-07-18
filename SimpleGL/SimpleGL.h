#pragma once



// Obs�uga okienka


// Inicjalizacja okna graficznego
void initGL(int w , int h);

// Zwolnienie zasob�w
void end();

// U�pienie w�tku 
void sleep(int miliseconds);

// Pauza do naci�ni�cia klawisza
void wait();


// Ustawienia



//
void setClearColor(int r , int g , int b);

// 

// Obs�uga b��d�w


// Wyrzuca message boxa z b��dem
void errorMsg(char * msg);

//Wyrzuca message boxa nast�pnie zwalnia pami�� i ko�czy program
void errorCritical(char * msg);


// Rysowanie



// Punkt
void point(float x , float y);

// Odcinek mi�dzy dwoma punktami
void line(float x1 , float y1 , float x2 , float y2);

// Ko�o o danym �rodku i promieniu
void circle(float x , float y , float r);

// Rysuje tekst w danym miejscu
void text(int x , int y , char * t);

// Czyszczenie ekranu
void clear();

// Ustawienie koloru RGB ( 0 - 255 )
void setColor(int r , int g , int b);



// Rysowanie obrazk�w


// Wczytuje plik do tekstury i zwraca ID
int loadImage(char * path);

// Rysuje teksture o ID w danym miejscu ( x , y , szeroko�� , wysoko��) x,y lewego dolnego wierzcho�ka
void drawImage(int ID , float left , float top , float right , float bottom);

// Ustawia podany kolor na zupe�nie przezroczyste t�o
void keyColor(int ID , int r , int g , int b);