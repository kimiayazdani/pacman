#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdlib.h>

Direction BFS(const Map* map, int fx, int fy, int lx, int ly)
{
    int i;
    coord * path = malloc(5 * sizeof(coord));
    path [0].x = fx;
    path [0].y = fy;
    path[DIR_RIGHT].x = (fx + 1)%map->width;
    path[DIR_RIGHT].y = fy;
    path[DIR_LEFT].x = (map->width + fx - 1)%map->width;
    path[DIR_LEFT].y = fy;
    path[DIR_DOWN].x = fx;
    path[DIR_DOWN].y = (fy + 1)%map->height;
    path[DIR_UP].x = fx;
    path[DIR_UP].y = (fy + map->height - 1)%map->height;
    int dirs[5];
    for(i = 0; i < 5; ++i)
        dirs[i] = 100000;
    for(i = 1; i < 5; ++i) {
        if (map->cells[path[i].x][path[i].y] == '#')
            continue;
        int j;
        int **checked = malloc(map->width * sizeof(int *));
        for(j = 0; j < map->width; ++j)
            checked[j] = malloc(map->height * sizeof(int));
        for(j = 0; j < 5; ++j)
            checked[path[j].x][path[j].y] = 1;
        dirs[i] = findPath(checked, map, &path[i], lx, ly, 1, 1);
    }
    int min = dirs[0];
    dirs[0] = -1;
    for(i = 1; i < 5; ++i)
        if(min > dirs[i])
        {
            min = dirs[i];
            dirs[0] = i;
        }
    return dirs[0];
}
int findPath(int ** checked, const Map* map, coord * prepath, int lx, int ly, int leng, int plen)
{
    coord * path = malloc(plen * 4 * sizeof(coord));
    int i;
    int prex, prey;
    int newplen = 0;
    for(i = 0; i < plen; ++i)
    {
        prex = prepath[i].x;
        prey = prepath[i].y;
        if(prex == lx && prey == ly)
            return leng;
        //up
        prey = (prey - 1 + map->height)%map->height;
        if(map->cells[prex][prey] != '#' && !checked[prex][prey])
        {
            checked[prex][prey] = 1;
            path[newplen].x = prex;
            path[newplen].y = prey;
            newplen = newplen + 1;
        }
        //down
        prey = (prey + 2)%map->height;
        if(map->cells[prex][prey] != '#' && !checked[prex][prey])
        {
            checked[prex][prey] = 1;
            path[newplen].x = prex;
            path[newplen++].y = prey;
        }
        prey = prepath[i].y;
        //left
        prex = (prex - 1 + map->width)%map->width;
        if(map->cells[prex][prey] != '#' && !checked[prex][prey])
        {
            checked[prex][prey] = 1;
            path[newplen].x = prex;
            path[newplen++].y = prey;
        }
        //right
        prex = (prex + 2)%map->width;
        if(map->cells[prex][prey] != '#' && !checked[prex][prey])
        {
            checked[prex][prey] = 1;
            path[newplen].x = prex;
            path[newplen++].y = prey;
        }
    }
    if(!newplen)
        return 100000;
    return findPath(checked, map, path, lx, ly, leng + 1, newplen);
}

Direction decideGhost(const Map* map, Ghost* ghost, Pacman* pacman, Ghost* blinky) {
    //
    if(ghost->type == BLINKY)
    {
        return BFS(map, ghost->x, ghost->y, pacman->x, pacman->y);
    }
//    //
    else if(ghost->type == PINKY)
    {
        if(pacman->dir == DIR_UP)
        {
            if(map->cells[(int) pacman->x][(int) (pacman->y - 1 + map->height)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) pacman->y);
            if(map->cells[(int) pacman->x][(int) (pacman->y - 2 + map->height)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y - 1 + map->height)%map->height);
            if(map->cells[(int) pacman->x][(int) (pacman->y - 3 + map->height)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y - 2 + map->height)%map->height);
            if(map->cells[(int) pacman->x][(int) (pacman->y - 4 + map->height)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y - 3 + map->height)%map->height);
            return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y - 4 + map->height)%map->height);
        }
        else if(pacman->dir == DIR_LEFT)
        {
            if(map->cells[(int) (pacman->x + map->width - 1)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) pacman->y);
            if(map->cells[(int) (pacman->x + map->width - 2)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y,(int) (pacman->x + map->width - 1)%map->width, (int) pacman->y);
            if(map->cells[(int) (pacman->x + map->width - 3)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y, (int) (pacman->x + map->width - 2)%map->width, (int) pacman->y);
            if(map->cells[(int) (pacman->x + map->width - 4)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y, (int) (pacman->x + map->width - 3)%map->width, (int) pacman->y);
            return BFS(map, ghost->x, ghost->y, (int) (pacman->x + map->width - 4)%map->width, (int) pacman->y);
        }
        else if(pacman->dir == DIR_RIGHT)
        {
            if(map->cells[(int) (pacman->x + 1)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) pacman->y);
            if(map->cells[(int) (pacman->x + 2)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y,(int) (pacman->x + 1)%map->width, (int) pacman->y);
            if(map->cells[(int) (pacman->x + 3)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y, (int) (pacman->x + 2)%map->width, (int) pacman->y);
            if(map->cells[(int) (pacman->x + 4)%map->width][(int) pacman->y] == '#')
                return BFS(map, ghost->x, ghost->y, (int) (pacman->x + 3)%map->width, (int) pacman->y);
            return BFS(map, ghost->x, ghost->y, (int) (pacman->x + 4)%map->width, (int) pacman->y);
        }
        else if(pacman->dir == DIR_DOWN)
        {
            if(map->cells[(int) pacman->x][(int) (pacman->y + 1)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) pacman->y);
            if(map->cells[(int) pacman->x][(int) (pacman->y + 2)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y + 1)%map->height);
            if(map->cells[(int) pacman->x][(int) (pacman->y + 3)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y + 2)%map->height);
            if(map->cells[(int) pacman->x][(int) (pacman->y + 4)%map->height] == '#')
                return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y + 3)%map->height);
            return BFS(map, ghost->x, ghost->y, pacman->x, (int) (pacman->y + 4)%map->height);
        }
//        else //dir NONE
//            return BFS(map, ghost->x, ghost->y, pacman->x, pacman->y);
    }
    else if(ghost->type == INKY)
    {
        if(pacman->dir == DIR_UP)
        {
            if(map->cells[(int) (2 * pacman->x - blinky->x + map->width)%map->width]
                    [(int) (2 * pacman->y - 4 - blinky->y + map->height)%map->height] != '#')
                return BFS(map, ghost->x, ghost->y, (int) (2 * pacman->x - blinky->x + map->width)%map->width,
                           (int) (2 * pacman->y - 4 - blinky->y + map->height)%map->height);
        }
        else if(pacman->dir == DIR_DOWN)
        {
            if(map->cells[(int) (2 * pacman->x - blinky->x + map->width)%map->width]
               [(int) (2 * pacman->y + 4 - blinky->y + map->height)%map->height] != '#')
                return BFS(map, ghost->x, ghost->y, (int) (2 * pacman->x - blinky->x + map->width)%map->width,
                           (int) (2 * pacman->y + 4 - blinky->y + map->height)%map->height);
        }
        else if(pacman->dir == DIR_LEFT)
        {
            if(map->cells[(int) (2 * pacman->x - 4 - blinky->x + map->width)%map->width]
               [(int) (2 * pacman->y - blinky->y + map->height)%map->height] != '#')
                return BFS(map, ghost->x, ghost->y, (int) (2 * pacman->x - 4 - blinky->x + map->width)%map->width,
                           (int) (2 * pacman->y - blinky->y + map->height)%map->height);
        }
        else if(pacman->dir == DIR_RIGHT)
        {
            if(map->cells[(int) (2 * pacman->x + 4 - blinky->x + map->width)%map->width]
               [(int) (2 * pacman->y - blinky->y + map->height)%map->height] != '#')
                return BFS(map, ghost->x, ghost->y, (int) (2 * pacman->x + 4 - blinky->x + map->width)%map->width,
                           (int) (2 * pacman->y - blinky->y + map->height)%map->height);
        }
        else //in case pacman's not moving...
        {
            if(map->cells[(int) (2 * pacman->x - blinky->x + map->width)%map->width]
               [(int) (2 * pacman->y - blinky->y + map->height)%map->height] != '#')
                return BFS(map, ghost->x, ghost->y, (int) (2 * pacman->x - blinky->x + map->width)%map->width,
                           (int) (2 * pacman->y - blinky->y + map->height)%map->height);
        }
    }
    else //clyde
    {
        if((ghost->x - pacman->x)*(ghost ->x - pacman->x) + (ghost->y - pacman->y)*(ghost->y - pacman->y) > 64)
            return BFS(map, ghost->x, ghost->y, pacman->x, pacman->y);
        if(map->cells[0][map->height - 1] != '#')
            return BFS(map, ghost->x, ghost->y, 0, map->height - 1);
    }
    while(1) {
        Direction newDirection = rand() % 4 + 1;
        if (newDirection == DIR_UP) {
            if (map->cells[(int) ghost->x][(int) (ghost->y - 1 + map->height) % map->height] != '#')
                return newDirection;
        }
        else if(newDirection == DIR_DOWN) {
            if (map->cells[(int) ghost->x][(int) (ghost->y + 1)%map->height] != '#')
                return newDirection;
        }
        else if(newDirection == DIR_RIGHT)
        {
            if (map->cells[(int) (ghost->x + 1)%map->width][(int) ghost->y] != '#')
                return newDirection;
        }
        else //right
        {
            if (map->cells[(int) (ghost->x - 1 + map->width)%map->width][(int) ghost->y] != '#')
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
//                    else
//                        return pacman->dir;
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
//                    else
//                        return pacman->dir;
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
//                    else
//                        return pacman->dir;
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
//                    else
//                        return pacman->dir;
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
//                    else
//                        return pacman->dir;
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
//                    else
//                        return pacman->dir;
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
//                    else
//                        return pacman->dir;
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
