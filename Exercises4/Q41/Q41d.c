#include "graphics.h"
#include <math.h>

int main(void)
{
    int cx = 250; // Circle centre
    int cy = 150;
    int r = 50;   // Circle radius
    int size = 25; // Square size

    background();
    setColour(green);
    fillArc(cx - r, cy - r, 2 * r, 2 * r, 0, 360);
    setColour(white);
    fillArc(cx - r + 15, cy - r + 15, 2 * (r - 15), 2 * (r - 15), 0, 360);

    foreground();

    for (int angle = 0; angle < 360; angle += 3)
    {
        clear();

        // Centre of the square moving along the circle
        double radians = angle * M_PI / 180.0;
        int x = cx + (int)(r * cos(radians));
        int y = cy + (int)(r * sin(radians));

        // Square rotation (rotate faster for visibility)
        double rotation = 10 * angle * M_PI / 180.0; 

        double half = size / 2.0;

        // Square’s local corner positions (before rotation)
        double localCorners[4][2] = {
            {-half, -half}, {half, -half}, {half, half}, {-half, half}
        };

        // Arrays to hold rotated screen coordinates
        int px[4], py[4];

        // Rotate and translate each corner
        for (int i = 0; i < 4; i++)
        {
            double lx = localCorners[i][0];
            double ly = localCorners[i][1];

            // Apply rotation
            double rx = lx * cos(rotation) - ly * sin(rotation);
            double ry = lx * sin(rotation) + ly * cos(rotation);

            // Translate to actual screen position
            px[i] = (int)(x + rx);
            py[i] = (int)(y + ry);
        }

        // Draw the rotated square
        setColour(blue);
        fillPolygon(4, px, py);

        sleep(30);
    }

    return 0;
}
