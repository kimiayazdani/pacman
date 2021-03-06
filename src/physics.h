#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "game.h"
#include "input.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

// TO WRITE
Direction decidePacman(const Map* map, Pacman* pacman, Action action);


// TO WRITE
Direction decideGhost(const Map* map, Ghost* ghost, Pacman* pacman, Ghost* blinky);
Direction BFS(const Map* map, int fx, int fy, int lx, int ly);
int findPath(int ** checked, const Map* map, coord * path, int lx, int ly, int leng, int plen);
#endif