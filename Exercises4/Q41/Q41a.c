#include "graphics.h"
#include <math.h>

int main(void)
{
    int cx = 250; 
    int cy = 150;
    int r = 50;       
    int size = 25;  

    // Draw the circle (background)
    background();
    setColour(green);
    fillArc(cx - r, cy - r, 2 * r, 2 * r, 0, 360);
    setColour(white);
    fillArc(cx - r + 15, cy - r + 15, 2 * (r - 15), 2 * (r - 15), 0, 360);

    int pathSize = 2 * r;          
    int topY = cy - r;        
    int leftX = cx - r; 
    int loops = 5;

    foreground();
    int i = 0;
    while (i <= loops) // loop forever
    {
        // move right across top edge
        for (int x = leftX; x <= leftX + pathSize; x += 2)
        {
            clear();
            setColour(blue);
            fillRect(x - size / 2, topY - size / 2, size, size);
            sleep(15);
        }

        // move down right edge
        for (int y = topY; y <= topY + pathSize; y += 2)
        {
            clear();
            setColour(blue);
            fillRect(leftX + pathSize - size / 2, y - size / 2, size, size);
            sleep(15);
        }

        // move left along bottom edge
        for (int x = leftX + pathSize; x >= leftX; x -= 2)
        {
            clear();
            setColour(blue);
            fillRect(x - size / 2, topY + pathSize - size / 2, size, size);
            sleep(15);
        }

        // move up left edge
        for (int y = topY + pathSize; y >= topY; y -= 2)
        {
            clear();
            setColour(blue);
            fillRect(leftX - size / 2, y - size / 2, size, size);
            sleep(15);
        }
        i++;
    }

    return 0;
}
