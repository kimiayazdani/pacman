#include <stdio.h>
#include "game.h"
#include "map.h"
#include <stdbool.h>
#include "physics.h"

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    // fill me
    FILE *fptr;
    fptr = fopen(filename, "r");
    fscanf(fptr, "%d %d", &outMap->height, &outMap->width);
    outGame->ghosts = 4;
    outGame->cheeses = 0;
    outGame->pineapples = 0;
    outGame->cherries = 0;
    outPacman->speed = PACMAN_DEFAULT_SPEED;
    int i, j;
    for(i = 0; i < outMap->height; ++i)
    {
        char line[100];
        fscanf(fptr, "%s\n", line);
        for(j = 0; j < outMap->width; ++j)
        {
            outMap->cells[j][i] = line[j];
            if(outMap->cells[j][i] == 'O')
                ++outGame->pineapples;
            else if(outMap->cells[j][i] == '*')
                ++outGame->cheeses;
            else if(outMap->cells[j][i] == '^')
                ++outGame->cherries;
        }
    }
    fscanf(fptr, "%d", &outGame->score);
    fscanf(fptr, "%*s %d %d (%d,%d) (%lf,%lf)", &outPacman->dir, &outPacman->health, &outPacman->startX, &outPacman->startY, &outPacman->x, &outPacman->y);
    for(i = 0; i < 4; i++)
    {
        outGhosts[i].type = i;
        int x = 0;
        fscanf(fptr, "%*s %d %d ", &outGhosts[i].dir, &x);
        if(x)
        {
            outGhosts[i].blue = false;
            outGhosts[i].blueCounterDown = 0;
        }
        else
        {
            outGhosts[i].blue = true;
            fscanf(fptr, "%d ", &outGhosts[i].blueCounterDown);
            outGhosts[i].blueCounterDown *= CYCLES_PER_SEC;
        }
        outGhosts[i].speed = GHOST_DEFAULT_SPEED;
        fscanf(fptr, "(%d,%d) (%lf,%lf)\n", &outGhosts[i].startX, &outGhosts[i].startY, &outGhosts[i].x, &outGhosts[i].y);
    }
}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    // fill me
    int pacX = outPacman->x + 0.5;
    int pacY= outPacman->y + 0.5;
    if(map->cells[pacX][pacY] == CELL_CHEESE)
    {
        map->cells[pacX][pacY] = CELL_EMPTY;
        outGame->score += CHEESE_SCORE;
        --outGame->cheeses;
    }
    if(map->cells[pacX][pacY] == CELL_CHERRY)
    {
        map->cells[pacX][pacY] = CELL_EMPTY;
        outGame->score += CHERRY_SCORE;
        --outGame->cherries;
    }
    if(map->cells[pacX][pacY] == CELL_PINEAPPLE)
    {
        map->cells[pacX][pacY] = CELL_EMPTY;
        outGame->score += PINEAPPLE_SCORE;
        --outGame->pineapples;
        int i;
        for(i = 0; i < 4; ++i)
        {
            outGhosts[i].blue = true;
            outGhosts[i].blueCounterDown = BLUE_DURATION;
        }
    }
}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {
    // fill me
}

bool isGameFinished(Game* game, Pacman* pacman) {
    // fill me
}

void checkGhostState(Ghost* ghost) {
    // fill me
}
