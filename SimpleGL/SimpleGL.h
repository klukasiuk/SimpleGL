/*************************************************************************
 * SimpleGL - www.github.com/mordimerr/simplegl
 * A simple graphics library for novice C/C++ programers
 * Based on : OpenGL , GLFW , SOIL and FTGL
 *------------------------------------------------------------------------
 *
 * Copyright (c) 2015 Konrad £ukasiuk
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
void setClearColor(double r , double g , double b);

// Ustawia wielkoœæ rysowanych punktów
void setPointSize(float size);

// Wczytuje czcionkê
void setFont(char * name);

// Ustawiam wielkoœæ czcionki
void setFontSize(int size);

// Ustawia podwójne buforowanie
void setDoubleBuffered(bool state);


// Zwraca czas od pocz¹tku programu
double getTime();


// Obs³uga b³êdów



// Wyrzuca message boxa z b³êdem
void errorMsg(char * msg);

//Wyrzuca message boxa nastêpnie zwalnia pamiêæ i koñczy program
void errorCritical(char * msg);


// Rzutowanie

// Ustawia rzutowanie prostok¹tne w okreœlonym obszarze
void view(float left , float top , float right , float bottom);

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

// Zamienia bufory okna , sprawdza eventy
void swap();


// Sprawdza eventy
void checkEvents();


// Rysowanie obrazków



// Wczytuje plik do tekstury i zwraca ID
int loadImage(char * path);

// Rysuje teksture o ID w danym miejscu ( x , y , szerokoœæ , wysokoœæ) x,y lewego dolnego wierzcho³ka
void drawImage(int ID , float left , float top , float right , float bottom);

// Ustawia podany kolor na zupe³nie przezroczyste t³o
void keyColor(int ID , int r , int g , int b);

// Zapisuje zrzut ekranu pod podan¹ nazw¹ w formacie BMP
void screenshot(char * filename);