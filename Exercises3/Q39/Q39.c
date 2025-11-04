#include <stdio.h>

int main(void) {
    int hours, minutes;

    printf("Enter time in 24-hour format (HH:MM): ");
    scanf("%d:%d", &hours, &minutes);

    char *period;

    if (hours < 12)
        period = "am";
    else
        period = "pm";

    // Convert hours to 12-hour format
    if (hours == 0)
        hours = 12;
    else if (hours > 12)
        hours %= 12;

    printf("Time in 12-hour format: %d:%02d%s\n", hours, minutes, period);

    return 0;
}
