## Overview

This program generates a **triangle shaped maze**, places a **robot** and **markers** inside it, and allows the robot to navigate through the maze while **avoiding obstacles** to pick up the markers.  
The maze is drawn visually using the **Java drawapp visualizer** (`drawapp-4.5.jar`), allowing you to see the robot’s movement and the maze structure in real time.

### Features
- **Maze generation** with configurable tile sizes and padding  
- **Triangular area** added within the maze  
- **Obstacle inversion logic** to ensure full connectivity  
- **Retry mechanism** to regenerate the maze if it becomes disconnected  
- **Dynamic rendering** via the external `drawapp` visualization tool  


## How It Works

1. The program initializes a maze based on **canvas** and **tile size** parameters.  
2. It generates **walls** and a **triangular arena**.  
3. The maze is **validated** to ensure all areas remain connected; if not, it’s automatically **regenerated**.  
4. Once the maze is ready, a **robot** is placed inside and moves through it according to programmed navigation logic and picks up all the markers.
5. Once the robot has navigated all possible tiles and picked up all markers in its way, it stops moving.  
6. The **output** of the C program is **piped** into the Java visualizer (`drawapp-4.5.jar`), which draws the maze and robot movements in real time.

## Command to run program

**Compile**: gcc -o main main.c maze.c robot.c graphics.c
**Run**: .\main.exe | java -jar drawapp-4.5.jar