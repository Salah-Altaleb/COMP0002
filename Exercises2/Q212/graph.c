#include "graphics.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(void) 
{   
    // --- Legend ---
    setColour(red);
    drawString("Sine (red)", 10, 20);
    setColour(blue);
    drawString("Cosine (blue)", 10, 40);
    setColour(green);
    drawString("Tangent (green)", 10, 60);

    // --- Axes ---
    setColour(black);
    drawLine(100, 150, 460, 150); // x-axis
    drawLine(100, 20, 100, 280);  // y-axis

    // --- Axis labels ---
    drawString("x", 470, 155);
    drawString("y", 98, 10);

    // --- Degree labels along x-axis ---
    drawString("0",   93, 165);
    drawString("90",  188, 165);
    drawString("180", 278, 165);
    drawString("270", 368, 165);
    drawString("360", 458, 165);

    // --- Y-axis labels (+1, -1 reference) ---
    drawString("+1", 75, 70);
    drawString("-1", 75, 230);

    int stretch = 80;

    // --- Starting points for sin/cos ---
    int x_prev = 100;
    int y_sin_prev = 150;
    int y_cos_prev = 150 - stretch;

    // --- Separate starting state for tangent ---
    int x_prev_tan = 100;
    int y_tan_prev = 150;
    bool tan_prev_valid = false;   // only true when we have a valid previous tan point

    const double EPS = 1e-6;      // threshold to avoid cos ~ 0

    for (int i = 0; i <= 360; i++) 
    { 
        double radians = i * M_PI / 180.0;
        int x = 100 + i;

        // --- Function values ---
        int y_sin = 150 - (int)(stretch * sin(radians));
        int y_cos = 150 - (int)(stretch * cos(radians));
        double cosValue = cos(radians);

        // --- Sine (red) ---
        setColour(red);
        drawLine(x_prev, y_sin_prev, x, y_sin);

        // --- Cosine (blue) ---
        setColour(blue);
        drawLine(x_prev, y_cos_prev, x, y_cos);

        // --- Tangent (green) ---
        setColour(green);

        // Check that cosine is not (near) zero so tan is defined
        if (fabs(cosValue) > EPS)
        {
            // scale tangent down so it fits the window
            int y_tan = 150 - (int)(stretch * tan(radians));

            // only draw if we have a valid previous tangent point
            if (tan_prev_valid) {
                drawLine(x_prev_tan, y_tan_prev, x, y_tan);
            }

            // update tangent previous point and mark valid
            x_prev_tan = x;
            y_tan_prev = y_tan;
            tan_prev_valid = true;
        }
        else
        {
            // when tan is undefined we simply mark previous as invalid
            // so the next valid point won't connect across the discontinuity
            tan_prev_valid = false;
        }

        // --- Update previous sin/cos points ---
        x_prev = x;
        y_sin_prev = y_sin;
        y_cos_prev = y_cos;
    }

    return 0;
}
