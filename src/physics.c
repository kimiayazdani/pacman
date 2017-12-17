#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdlib.h>

Direction decideGhost(const Map* map, Ghost* ghost) {
    // fill me
    Direction newDirection = rand() % 5 + 1;
    if(newDirection == 5)
        newDirection = -1;
    if(newDirection == DIR_NONE)
        return newDirection;
    if (newDirection == DIR_UP)
    {
        if(ghost->y)
        {
            if (map->cells[(int) ghost->x][(int) ghost->y - 1] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
        else
        {
            if (map->cells[(int) ghost->x][map->height - 1] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
    }
    if(newDirection == DIR_DOWN)
    {
        if(ghost->y != map->height - 1)
        {
            if (map->cells[(int) ghost->x][(int) ghost->y + 1] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
        else
        {
            if (map->cells[(int) ghost->x][0] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
    }
    if(newDirection == DIR_RIGHT)
    {
        if(ghost->x != map->width - 1)
        {
            if (map->cells[(int) ghost->x + 1][(int) ghost->y] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
        else
        {
            if (map->cells[0][(int) ghost->y] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
    }
    if(newDirection == DIR_LEFT)
    {
        if(ghost->x)
        {
            if (map->cells[(int) ghost->x - 1][(int) ghost->y] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
        else
        {
            if(map->cells[map->width - 1][(int) ghost->y] == '#')
                decideGhost(map, ghost);
            else
                return newDirection;
        }
    }
}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    // fill me
    if(action & MOVE_ACTION_MASK)
    {
        if(action == ACTION_LEFT)
        {
            if(pacman->x)
            {
                if (map->cells[(int) pacman->x - 1][(int) pacman->y] == '#')
                {
                    if(pacman->dir == DIR_LEFT)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_LEFT;
            }
            else
            {
                if(map->cells[map->width - 1][(int) pacman->y] == '#')
                {
                    if(pacman->dir == DIR_LEFT)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_LEFT;
            }
        }
        if(action == ACTION_RIGHT)
        {
            if(pacman->x != map->width - 1)
            {
                if (map->cells[(int) pacman->x + 1][(int) pacman->y] == '#')
                {
                    if(pacman->dir == DIR_RIGHT)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_RIGHT;
            }
            else
            {
                if (map->cells[0][(int) pacman->y] == '#')
                {
                    if(pacman->dir == DIR_RIGHT)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_RIGHT;
            }
        }
        if(action == ACTION_DOWN)
        {
            if(pacman->y != map->height - 1)
            {
                if (map->cells[(int) pacman->x][(int) pacman->y + 1] == '#')
                {
                    if(pacman->dir == DIR_DOWN)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_DOWN;
            }
            else
            {
                if (map->cells[(int) pacman->x][0] == '#')
                {
                    if(pacman->dir == DIR_DOWN)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_DOWN;
            }
        }
        if(action == ACTION_UP)
        {
            if(pacman->y)
            {
                if (map->cells[(int) pacman->x][(int) pacman->y - 1] == '#')
                {
                    if(pacman->dir == DIR_UP)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_UP;
            }
            else
            {
                if (map->cells[(int) pacman->x][map->height - 1] == '#')
                {
                    if(pacman->dir == DIR_UP)
                        return DIR_NONE;
                    else
                        return pacman->dir;
                }
                else
                    return DIR_UP;
            }
        }
    }
    if(pacman->dir == DIR_NONE)
        return DIR_NONE;
    if (pacman->dir == DIR_UP)
    {
        if(pacman->y)
        {
            if (map->cells[(int) pacman->x][(int) pacman->y - 1] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
        else
        {
            if (map->cells[(int) pacman->x][map->height - 1] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
    }
    if(pacman->dir == DIR_DOWN)
    {
        if(pacman->y != map->height - 1)
        {
            if (map->cells[(int) pacman->x][(int) pacman->y + 1] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
        else
        {
            if (map->cells[(int) pacman->x][0] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
    }
    if(pacman->dir == DIR_RIGHT)
    {
        if(pacman->x != map->width - 1)
        {
            if (map->cells[(int) pacman->x + 1][(int) pacman->y] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
        else
        {
            if (map->cells[0][(int) pacman->y] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
    }
    if(pacman->dir == DIR_LEFT)
    {
        if(pacman->x)
        {
            if (map->cells[(int) pacman->x - 1][(int) pacman->y] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
        else
        {
            if(map->cells[map->width - 1][(int) pacman->y] == '#')
                return DIR_NONE;
            else
                return pacman->dir;
        }
    }
}
