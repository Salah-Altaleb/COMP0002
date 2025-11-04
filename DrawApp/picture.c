#include "graphics.h"

int main(void)
{
 drawLine(0,0,499,299);
 setColour(green);
 fillRect(150,50,100,200);
 setColour(blue);
 fillArc(150,0,100,100,0,180);
 setColour(red);
 drawStringRotated("House!",150,250,-90);
 return 0;
}