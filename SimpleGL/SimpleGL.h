#pragma once


// Obs³uga okienka



// Inicjalizacja okna graficznego
void initGL(int w , int h);

// Zwolnienie zasobów
void end();

// Uœpienie w¹tku 
void sleep(int miliseconds);

// Pauza do naciœniêcia klawisza
void wait();


// Ustawienia



// Ustawia kolor czysczenia ekranu
void setClearColor(int r , int g , int b);

// Ustawia wielkoœæ rysowanych punktów
void setPointSize(float size);

// Wczytuje czcionkê
void setFont(char * name);

// Ustawiam wielkoœæ czcionki
void setFontSize(int size);


// Obs³uga b³êdów



// Wyrzuca message boxa z b³êdem
void errorMsg(char * msg);

//Wyrzuca message boxa nastêpnie zwalnia pamiêæ i koñczy program
void errorCritical(char * msg);


// Rzutowanie

// Ustawia rzutowanie prostok¹tne w okreœlonym obszarze
void View(float left , float top , float right , float bottom);

// Wybiera warstwê
void selectLayer(int layer);


// Rysowanie



// Punkt ( wielkoœc okreœle setPointSize)
void point(float x , float y);

// Odcinek miêdzy dwoma punktami
void line(float x1 , float y1 , float x2 , float y2);

// Ko³o o danym œrodku i promieniu
void circle(float x , float y , float r);

// Wielok¹t ( tablica x , tablica y , iloœæ wierzcho³ków)
void polygon( float * x , float * y , int n);

// Rysuje tekst w danym miejscu
void text(float x , float y , char * t);

// Czyszczenie ekranu
void clear();

// Ustawienie koloru RGB ( 0 - 255 )
void setColor(int r , int g , int b);

// Ustawia szary kolor ( 0 - 255 )
void setGray(int value);


// Rysowanie obrazków



// Wczytuje plik do tekstury i zwraca ID
int loadImage(char * path);

// Rysuje teksture o ID w danym miejscu ( x , y , szerokoœæ , wysokoœæ) x,y lewego dolnego wierzcho³ka
void drawImage(int ID , float left , float top , float right , float bottom);

// Ustawia podany kolor na zupe³nie przezroczyste t³o
void keyColor(int ID , int r , int g , int b);

// Zapisuje zrzut ekranu pod podan¹ nazw¹ w formacie BMP
void screenshot(char * filename);