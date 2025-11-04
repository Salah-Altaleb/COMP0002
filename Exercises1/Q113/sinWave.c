#include "graphics.h"
#include <stdio.h>
#include <math.h>

int main(void) 
{ 
    int x1 = 100;
    int y1 = 150; 
    for (int i = 0; i <= 360; i++) 
    { 
        int x2 = 100 + i; 
        int y2 = 150 - (int)(100 * sin(i * M_PI / 180.0)); 
        drawLine(x1, y1, x2, y2); 
        x1 = x2; 
        y1 = y2; 
    }

    return 0;
}