#include "graphics.h"
#include <math.h>

int main(void) 
{   
    int x_center = 250;
    int y_center = 150;

    for (int i = 0; i <= 5 * 360; i += 5) 
    { 
        double radians = i * M_PI / 180.0;
        double radius = 0.05 * i;
        int x = x_center + (int)(radius * cos(radians));
        int y = y_center - (int)(radius * sin(radians));
        drawRect(x, y, 1, 1);

    }
    return 0;
}
