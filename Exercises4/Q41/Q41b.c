#include "graphics.h"
#include <math.h>

int main(void)
{
    int cx = 250; 
    int cy = 150;
    int r = 50;       
    int size = 25;  

    background();
    setColour(green);
    fillArc(cx - r, cy - r, 2 * r, 2 * r, 0, 360);
    setColour(white);
    fillArc(cx - r + 15, cy - r + 15, 2 * (r - 15), 2 * (r - 15), 0, 360);

    foreground();
    for (int angle = 0; angle < 360; angle += 1)
    {
        clear();

        double radians = angle * M_PI / 180.0;
        int x = cx + (int)(r * cos(radians));
        int y = cy + (int)(r * sin(radians));

        setColour(blue);
        fillRect(x - size / 2, y - size / 2, size, size);

        sleep(30);
    }

    return 0;
}
