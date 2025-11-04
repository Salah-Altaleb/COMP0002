#include "graphics.h"

int main(void)
{
    int centreX = 250;
    int centreY = 150;

    drawOval(centreX - 150, centreY - 75, 300, 150);
    drawOval(centreX - 100, centreY - 50, 200, 100);
    drawOval(centreX - 50, centreY - 25, 100, 50);
    drawOval(centreX - 25, centreY - 12, 50, 25);

    return 0;
}
