#! /bin/bash

sudo apt-get install libsoil-dev libftgl-dev libsdl2-dev

sudo apt-get build-dep glfw

wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip

unzip glfw-3.2.1.zip

cd glfw-3.2.1
sudo cmake -G "Unix Makefiles"
sudo make
sudo make install

sudo g++ -Wall main.cpp msgbox.cpp SimpleGL.cpp msgbox.h SimpleGL.h -o sgl.exec -std=c++11 -I/usr/include/freetype2 -lglfw3 -lSOIL - lftgl -lSDL2 -lSDL2main -lGL -lGLU `pkg-config --static --libs glfw3` `pkg-config --static --libs sdl2`