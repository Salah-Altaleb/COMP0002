#include "maze.h"
#include "robot.h"
#include "graphics.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    srand((unsigned)time(NULL));

    int TILE_SIZE = 40;
    int MAX_ARENA = 600;
    int PADDING = 1 * TILE_SIZE;

    int minTiles = 7;
    int maxTiles = MAX_ARENA / TILE_SIZE;

    int cols = rand() % (maxTiles - minTiles + 1) + minTiles;
    int rows = rand() % (maxTiles - minTiles + 1) + minTiles;

    int CANVAS_WIDTH = cols * TILE_SIZE;
    int CANVAS_HEIGHT = rows * TILE_SIZE;

    int delay_ms = 200;

    Maze maze;
    Robot robot;

    background();
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);

    if (!maze_init(&maze, CANVAS_WIDTH, CANVAS_HEIGHT, TILE_SIZE, PADDING)) {
        fprintf(stderr, "Failed to init maze\n");
        maze_free(&maze);
        return 1;
    }

    if (!maze_place_random_marker(&maze)) {
        fprintf(stderr, "Failed to place marker\n");
        maze_free(&maze);
        return 1;
    }

    if (!robot_init_random(&robot, &maze)) {
        fprintf(stderr, "Failed to place robot\n");
        maze_free(&maze);
        return 1;
    }

    // Draw the static maze once on the background
    background();
    maze_draw(&maze);

    // Main loop: update foreground only
    dfs_find_marker(&robot, delay_ms);

    // If the robot is carrying a marker
    if (markerCount(&robot) > 0) {
        // Case 1: Robot found the marker at a corner → go to another corner
        if (atCorner(&robot)) {
            printf("Found marker at a corner — moving to another corner...\n");

            // Try to move to any other corner
            while (atCorner(&robot)) {
                // Move forward if possible, else rotate until possible
                if (canMoveForward(&robot)) forward(&robot);
                else right(&robot);
                render_state(&robot, delay_ms);
            }

            // Continue moving until we reach a new corner
            while (!atCorner(&robot)) {
                if (canMoveForward(&robot)) forward(&robot);
                else right(&robot);
                render_state(&robot, delay_ms);
            }

            dropMarker(&robot);
            render_state(&robot, delay_ms);
        }

        // Case 2: Robot found the marker somewhere in the maze → go to a corner
        else {
            printf("Found marker in the maze — moving to nearest corner...\n");

            while (!atCorner(&robot)) {
                if (canMoveForward(&robot)) forward(&robot);
                else right(&robot);
                render_state(&robot, delay_ms);
            }

            dropMarker(&robot);
            render_state(&robot, delay_ms);
        }
    }

    sleep(delay_ms * 5);
    maze_free(&maze);
    robot_free(&robot);
    return 0;
}