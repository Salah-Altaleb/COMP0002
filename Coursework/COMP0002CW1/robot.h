#ifndef ROBOT_H
#define ROBOT_H

#include "maze.h"

typedef enum { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 } Direction;

typedef struct Robot {
    int col;
    int row;
    Direction dir;
    int carrying;
    Maze *maze;
    int **visited;
    int has_moved_since_pickup;
} Robot;

int robot_init_random(Robot *r, Maze *m);
void robot_free(Robot *r);

void render_state(Robot *r, int delay_ms);
void robot_draw(Robot *r);

int canMoveForward(Robot *r);
void forward(Robot *r);
void left(Robot *r);
void right(Robot *r);
int atCorner(Robot *r);
int atMarker(Robot *r);
void pickUpMarker(Robot *r);
void dropMarker(Robot *r);
int markerCount(Robot *r);

int dfs_find_marker(Robot *r, int delay_ms);

#endif // ROBOT_H
