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
        //age joloye pac divar bud bayad vaste
        //age un vary ke gharar bud bere divar bud bayad unghad bere ta avalin jayi ke mitunest bepiche tu
        
    }
}
