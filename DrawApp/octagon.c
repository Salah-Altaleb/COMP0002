#include "graphics.h"
#include <math.h>

int main(void)
{
  // I want to loop from 0 to 7 and draw a line each time, the angle starts at 0 and increases by 
  // 45 degrees each time
  setColour(black);
  int lineLength = 70;
  int startX = 100;
  int startY = 50;
  for (int i = 0; i < 8; i++)
  { 
    double angle = i * (M_PI / 4); 
    drawLine(startX, startY, startX + lineLength * cos(angle), startY + lineLength * sin(angle));
    startX += lineLength * cos(angle);
    startY += lineLength * sin(angle);
  }

  // Another method is to establish a centre point and draw the vertices of the octagon relative to that
  int centreX = 300;
  int centreY = 100;
  int sideLength = 50;
  int sides = 8;
  double interiorAngle = (sides - 2) * M_PI / sides; // in radians
  
  return 0;
}