#include "graphics.h"

int main(void)
{
    int centreX = 250;
    int centreY = 150;

    drawArc(centreX - 150, centreY - 90, 300, 180, 0, 180);
    drawArc(centreX - 125, centreY - 75, 250, 150, 0, 180);
    drawArc(centreX - 100, centreY - 60, 200, 120, 0, 180);
    drawArc(centreX - 75, centreY - 45, 150, 90, 0, 180);
    drawArc(centreX - 50, centreY - 30, 100, 60, 0, 180);
    drawArc(centreX - 25, centreY - 15, 50, 30, 0, 180);

    return 0;
}
