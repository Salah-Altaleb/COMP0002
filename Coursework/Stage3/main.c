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

    // Navigate to corner
    while (!atCorner(&robot)) {
        if (canMoveForward(&robot)) forward(&robot);
        else right(&robot);
        render_state(&robot, delay_ms);
    }

    // Drop marker only if robot has moved since pickup
    if (markerCount(&robot) > 0 && robot.hasMovedSincePickup && atCorner(&robot)) {
        dropMarker(&robot);
        render_state(&robot, delay_ms);
    }

    // If marker was originally in a corner, move to another corner first
    else if (markerCount(&robot) > 0 && !robot.hasMovedSincePickup) {
        // For simplicity, move to top-right corner
        while (!(robot.col == robot.maze->cols - 2 && robot.row == 1)) {
            if (canMoveForward(&robot)) forward(&robot);
            else right(&robot);
            render_state(&robot, delay_ms);
        }
        dropMarker(&robot);
        render_state(&robot, delay_ms);
    }

    sleep(delay_ms * 5);
    maze_free(&maze);
    robot_free(&robot);
    return 0;
}