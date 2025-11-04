#ifndef ROBOT_H
#define ROBOT_H

#include "maze.h"

typedef enum { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 } Direction;

typedef struct Robot {
    int col;       // tile column
    int row;       // tile row
    Direction dir;
    int carrying;  // number of markers carried
    Maze *maze;    // pointer to maze to query walls/markers
} Robot;

// initialize robot in a random tile that is NOT next-to-wall and not a wall tile.
// returns 1 if successful
int robot_init_random(Robot *r, Maze *m);

// drawing the robot at current tile (uses graphics.h)
void robot_draw(Robot *r);

// movement API required by assignment
void forward(Robot *r);
void left(Robot *r);
void right(Robot *r);
int atCorner(Robot *r);
int atMarker(Robot *r);
int canMoveForward(Robot *r);
void pickUpMarker(Robot *r);
void dropMarker(Robot *r);
int markerCount(Robot *r);

#endif // ROBOT_H
