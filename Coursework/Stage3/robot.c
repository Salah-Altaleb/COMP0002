#include "robot.h"
#include "graphics.h"
#include <stdlib.h>

// Helper: get tile in front given current direction
static void tile_in_front(Robot *r, int *outC, int *outR) {
    int c = r->col, ro = r->row;
    switch (r->dir) {
        case NORTH: ro -= 1; break;
        case SOUTH: ro += 1; break;
        case EAST:  c += 1; break;
        case WEST:  c -= 1; break;
    }
    if (outC) *outC = c;
    if (outR) *outR = ro;
}

int robot_init_random(Robot *r, Maze *m) {
    if (!r || !m) return 0;
    r->maze = m;
    // collect candidate tiles that are not wall and NOT adjacent to any wall
    int cap = m->cols * m->rows;
    int *cand = malloc(cap * sizeof(int));
    int count = 0;
    for (int row = 1; row < m->rows - 1; ++row) {
        for (int col = 1; col < m->cols - 1; ++col) {
            if (m->wall[col][row]) continue;
            // ensure not on marker
            if (m->marker[col][row]) continue;
            cand[count++] = col + row * m->cols;
        }
    }
    if (count == 0) {
        free(cand);
        return 0;
    }
    int idx = rand() % count;
    int val = cand[idx];
    r->col = val % m->cols;
    r->row = val / m->cols;
    r->dir = (Direction)(rand() % 4);
    r->carrying = 0;
    free(cand);

    r->visited = malloc(m->cols * sizeof(int *));
    for (int c = 0; c < m->cols; ++c) {
        r->visited[c] = calloc(m->rows, sizeof(int));
    }
    return 1;
}

void robot_free(Robot *r) {
    if (!r) return;
    if (r->visited) {
        for (int c = 0; c < r->maze->cols; ++c) free(r->visited[c]);
        free(r->visited);
        r->visited = NULL;
    }
}

void render_state(Robot *r, int delay_ms) {
    foreground();
    clear();
    maze_draw_markers(r->maze);
    robot_draw(r);
    sleep(delay_ms);
}

void robot_draw(Robot *r) {
    if (!r || !r->maze) return;
    int px, py;
    maze_tile_to_pixel(r->maze, r->col, r->row, &px, &py);
    // draw circle with small arrow indicating direction
    int cx = px + r->maze->tileSize/2;
    int cy = py + r->maze->tileSize/2;
    int rad = r->maze->tileSize/3;
    setColour(blue);
    fillOval(cx - rad, cy - rad, 2 * rad, 2 * rad);
    setColour(white);
    // arrow line
    int ax = cx, ay = cy;
    switch (r->dir) {
        case NORTH: ay = cy - rad; break;
        case SOUTH: ay = cy + rad; break;
        case EAST:  ax = cx + rad; break;
        case WEST:  ax = cx - rad; break;
    }
    drawLine(cx, cy, ax, ay);
}

int canMoveForward(Robot *r) {
    if (!r || !r->maze) return 0;
    int c, ro;
    tile_in_front(r, &c, &ro);
    // can't move if out of bounds or if wall
    return !maze_is_wall_tile(r->maze, c, ro);
}

void forward(Robot *r) {
    if (canMoveForward(r)) {
        int c, ro;
        tile_in_front(r, &c, &ro);
        r->col = c;
        r->row = ro;
    }
    r->hasMovedSincePickup = 1;
}

void left(Robot *r) {
    r->dir = (Direction)((r->dir + 3) % 4);
}

void right(Robot *r) {
    r->dir = (Direction)((r->dir + 1) % 4);
}

int atCorner(Robot *r) {
    if (!r || !r->maze) return 0;
    Maze *m = r->maze;
    int c = r->col;
    int ro = r->row;

    int wallUp = (ro > 0 && m->wall[c][ro - 1]);
    int wallDown = (ro < m->rows - 1 && m->wall[c][ro + 1]);
    int wallLeft = (c > 0 && m->wall[c - 1][ro]);
    int wallRight = (c < m->cols - 1 && m->wall[c + 1][ro]);

    // check for perpendicular wall combinations
    if ((wallUp && wallLeft) ||
        (wallUp && wallRight) ||
        (wallDown && wallLeft) ||
        (wallDown && wallRight)) {
        return 1;
    }

    return 0;
}

int atMarker(Robot *r) {
    if (!r || !r->maze) return 0;
    return maze_has_marker_tile(r->maze, r->col, r->row);
}

void pickUpMarker(Robot *r) {
    if (!r || !r->maze) return;
    if (maze_has_marker_tile(r->maze, r->col, r->row)) {
        r->carrying += 1;
        maze_remove_marker(r->maze, r->col, r->row);
    }
    r->hasMovedSincePickup = 0;
}

void dropMarker(Robot *r) {
    if (!r || !r->maze) return;
    if (r->carrying > 0 && !maze_has_marker_tile(r->maze, r->col, r->row)) {
        r->carrying -= 1;
        r->maze->marker[r->col][r->row] = 1;
    }
}

int markerCount(Robot *r) {
    if (!r) return 0;
    return r->carrying;
}

int dfs_find_marker(Robot *r, int delay_ms) {
    if (markerCount(r) > 0) return 1;

    r->visited[r->col][r->row] = 1;

    if (atMarker(r)) {
        pickUpMarker(r);
        render_state(r, delay_ms);
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        int nextCol = r->col, nextRow = r->row;
        switch (r->dir) {
            case NORTH: nextRow--; break;
            case SOUTH: nextRow++; break;
            case EAST:  nextCol++; break;
            case WEST:  nextCol--; break;
        }

        if (canMoveForward(r) && !r->visited[nextCol][nextRow]) {
            forward(r);
            render_state(r, delay_ms);

            if (dfs_find_marker(r, delay_ms)) return 1;

            // backtrack
            right(r);
            right(r);
            forward(r);
            render_state(r, delay_ms);
            right(r);
            right(r);
        }

        right(r);
    }

    return 0;
}