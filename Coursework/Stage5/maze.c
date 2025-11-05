#include "maze.h"
#include "graphics.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

static int **alloc_int_grid(int cols, int rows) {
    int **grid = malloc(cols * sizeof(int*));
    if (!grid) return NULL;
    for (int c = 0; c < cols; ++c) {
        grid[c] = calloc(rows, sizeof(int));
        if (!grid[c]) {
            // free partial
            for (int i = 0; i < c; ++i) free(grid[i]);
            free(grid);
            return NULL;
        }
    }
    return grid;
}

int maze_init(Maze *m, int canvasW, int canvasH, int tileSize, int padding) {
    if (!m) return 0;
    m->tileSize = tileSize;
    m->padding = padding;
    // compute usable area and the number of tiles vertically and horizontally
    int usableW = canvasW - 2 * padding;
    int usableH = canvasH - 2 * padding;
    if (usableW <= 0 || usableH <= 0) return 0;
    m->cols = usableW / tileSize;
    m->rows = usableH / tileSize;
    if (m->cols <= 0 || m->rows <= 0) return 0;

    m->wall = alloc_int_grid(m->cols, m->rows);
    m->marker = alloc_int_grid(m->cols, m->rows);
    if (!m->wall || !m->marker) return 0;

    // place surrounding walls (edge tiles flagged as walls)
    for (int c = 0; c < m->cols; ++c) {
        m->wall[c][0] = 1;
        m->wall[c][m->rows - 1] = 1;
    }
    for (int r = 0; r < m->rows; ++r) {
        m->wall[0][r] = 1;
        m->wall[m->cols - 1][r] = 1;
    }

    // Generate special arena (triangle + inversion + check)
    if (!maze_generate_special_arena(m, canvasW, canvasH, tileSize, padding)) {
        fprintf(stderr, "Failed to generate special arena.\n");
        maze_free(m);
        return 0;
    }

    // empty markers initially
    return 1;
}

int maze_generate_special_arena(Maze *m, int canvasW, int canvasH, int tileSize, int padding) {
    /* 1. Create a filled triangular region */
    int top_row = 1;
    int base_row = m->rows - 2;
    int cx = m->cols / 2;
    int max_half_width = m->cols / 2;

    for (int row = top_row; row <= base_row; ++row) {
        double frac = (double)(row - top_row) / (double)(base_row - top_row);
        int half_width = (int)(frac * max_half_width);

        int left_col = cx - half_width;
        int right_col = cx + half_width;

        for (int col = left_col; col <= right_col; ++col) {
            if (col <= 0 || col >= m->cols - 1 || row <= 0 || row >= m->rows - 1)
                continue;
            if (m->wall[col][row]) continue;

            m->wall[col][row] = 1;
            if (!is_fully_connected(m))
                m->wall[col][row] = 0;
        }
    }

    /* 2. Invert the arena interior */
    for (int r = 1; r < m->rows - 1; r++) {
        for (int c = 1; c < m->cols - 1; c++) {
            m->wall[c][r] = !m->wall[c][r];
        }
    }

    /* 3. Verify connectivity; retry if disconnected */
    int retries = 0;
    while (retries < 5 && !is_fully_connected(m)) {
        printf("Maze disconnected after inversion. Retrying (%d)...\n", retries + 1);
        retries++;

        maze_free(m);
        if (!maze_init(m, canvasW, canvasH, tileSize, padding))
            fprintf(stderr, "Failed to regenerate maze after disconnection.\n");
        return 0;
    }

    if (retries == 5) {
        fprintf(stderr, "Maze generation failed after 5 attempts.\n");
        return 0;
    }

    return 1;
}

void maze_free(Maze *m) {
    if (!m) return;
    if (m->wall) {
        for (int c = 0; c < m->cols; ++c) free(m->wall[c]);
        free(m->wall);
        m->wall = NULL;
    }
    if (m->marker) {
        for (int c = 0; c < m->cols; ++c) free(m->marker[c]);
        free(m->marker);
        m->marker = NULL;
    }
}

void maze_tile_to_pixel(Maze *m, int col, int row, int *outX, int *outY) {
    if (!m || !outX || !outY) return;
    *outX = m->padding + col * m->tileSize;
    *outY = m->padding + row * m->tileSize;
}

void maze_draw(Maze *m) {
    if (!m) return;
    // draw tiles
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            int px, py;
            maze_tile_to_pixel(m, c, r, &px, &py);
            setColour(white);
            fillRect(px, py, m->tileSize - 1, m->tileSize - 1);
            setColour(black);
            drawRect(px, py, m->tileSize - 1, m->tileSize - 1);
        }
    }
    // draw border
    setColour(red);
    drawRect(m->padding - 1, m->padding - 1, m->cols * m->tileSize + 1, m->rows * m->tileSize + 1);

    // draw walls (fill cell with dark grey)
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            if (m->wall[c][r]) {
                int px, py;
                maze_tile_to_pixel(m, c, r, &px, &py);
                setColour(darkgray);
                fillRect(px+1, py+1, m->tileSize-2, m->tileSize-2);
            }
        }
    }
}

void maze_draw_markers(Maze *m) {
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            if (m->marker[c][r]) {
                int px, py;
                maze_tile_to_pixel(m, c, r, &px, &py);
                int cx = px + m->tileSize / 2;
                int cy = py + m->tileSize / 2;
                int rad = m->tileSize / 2; // was 5
                setColour(green);
                fillOval(cx - rad, cy - rad, 2 * rad, 2 * rad);
            }
        }
    }
}

int maze_is_wall_tile(Maze *m, int col, int row) {
    if (!m) return 1;
    if (col < 0 || col >= m->cols || row < 0 || row >= m->rows) return 1;
    return m->wall[col][row];
}

int maze_has_marker_tile(Maze *m, int col, int row) {
    if (!m) return 0;
    if (col < 0 || col >= m->cols || row < 0 || row >= m->rows) return 0;
    return m->marker[col][row];
}

void maze_remove_marker(Maze *m, int col, int row) {
    if (!m) return;
    if (col < 0 || col >= m->cols || row < 0 || row >= m->rows) return;
    m->marker[col][row] = 0;
}

int maze_place_random_marker(Maze *m) {
    if (!m) return 0;
    // collect candidate tiles that are NOT wall and have at least one orthogonal neighbor that IS wall
    int capacity = m->cols * m->rows;
    int *candidates = malloc(capacity * sizeof(int)); // store index = col + row*cols
    int count = 0;
    for (int r = 1; r < m->rows - 1; ++r) {
        for (int c = 1; c < m->cols - 1; ++c) {
            if (m->wall[c][r] || m->marker[c][r]) continue;
            candidates[count++] = c + r * m->cols;
        }
    }
    if (count == 0) {
        free(candidates);
        return 0;
    }
    int idx = rand() % count;
    int val = candidates[idx];
    int col = val % m->cols;
    int row = val / m->cols;
    m->marker[col][row] = 1;
    free(candidates);
    return 1;
}

void add_random_obstacle(Maze *maze) {
    int r, c;
    int tries = 0;

    while (tries < 1000) {  // avoid infinite loops
        r = rand() % maze->rows;
        c = rand() % maze->cols;
        tries++;

        // Skip borders or existing walls
        if (maze->wall[r][c] == 1 || r == 0 || c == 0 ||
            r == maze->rows - 1 || c == maze->cols - 1)
            continue;

        // Temporarily set it as a wall
        maze->wall[r][c] = 1;

        // Check connectivity
        if (is_fully_connected(maze)) {
            // ✅ Keep it, connectivity preserved
            return;
        } else {
            // ❌ Undo it and try another position
            maze->wall[r][c] = 0;
        }
    }

    printf("Warning: Could not place more obstacles without disconnecting maze.\n");
}

bool is_fully_connected(Maze *maze) {
    int rows = maze->rows;
    int cols = maze->cols;

    // Create a visited array
    int **visited = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        visited[i] = calloc(cols, sizeof(int));
    }

    // Find a starting non-wall tile
    int startR = -1, startC = -1;
    for (int r = 0; r < rows && startR == -1; ++r) {
        for (int c = 0; c < cols && startC == -1; ++c) {
            if (maze->wall[r][c] == 0) {
                startR = r;
                startC = c;
            }
        }
    }

    // No empty cells → trivially connected
    if (startR == -1) {
        for (int i = 0; i < rows; ++i) free(visited[i]);
        free(visited);
        return true;
    }

    // Recursive flood fill
    dfs_fill(maze, visited, startR, startC);

    // Count total free tiles and visited ones
    int totalFree = 0, totalVisited = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (maze->wall[r][c] == 0) totalFree++;
            if (visited[r][c]) totalVisited++;
        }
    }

    for (int i = 0; i < rows; ++i) free(visited[i]);
    free(visited);

    return totalFree == totalVisited;
}

void dfs_fill(Maze *maze, int **visited, int r, int c) {
    if (r < 0 || c < 0 || r >= maze->rows || c >= maze->cols) return;
    if (maze->wall[r][c] == 1 || visited[r][c]) return;

    visited[r][c] = 1;

    dfs_fill(maze, visited, r + 1, c);
    dfs_fill(maze, visited, r - 1, c);
    dfs_fill(maze, visited, r, c + 1);
    dfs_fill(maze, visited, r, c - 1);
}
