#include "SimpleGL.h"


int main()
{
  initGL(640,480);

  setColor(255,0,255);

  line( 0,0,300,300);

  setFontSize(22);

  setColor(0,255,255);

  text(400,100,"SimpleGL");

  setFont("calibri.ttf");

  setFontSize(14);

  text(400,150,"SimpleGL");

  circle(200,200,200);

  int mario = loadImage("mario.png");

  keyColor(mario,0,255,255);

  drawImage(mario, 400,350,48*2,2*64);

  setPointSize(6);

  setColor(255,10,10);

  point(400,50);

  wait();

  end();
}