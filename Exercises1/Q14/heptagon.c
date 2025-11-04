#include "graphics.h"
#include <math.h>

int main(void)
{
    setColour(black);

    int centreX = 300;
    int centreY = 100;
    int radius = 50;
    int sides = 7;

    double step = 2 * M_PI / sides;
    double angle = M_PI / 2;

    int x1 = centreX + radius * cos(angle);
    int y1 = centreY - radius * sin(angle);

    for (int i = 1; i <= sides; i++) {
        angle += step;
        int x2 = centreX + radius * cos(angle);
        int y2 = centreY - radius * sin(angle);

        drawLine(x1, y1, x2, y2);

        x1 = x2;
        y1 = y2;
    }

    return 0;
}
