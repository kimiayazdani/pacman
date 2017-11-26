#include <stdio.h>
struct ghost{
	//0: Blinky, 1: Pinky, 2:Clyde, 3:Inky
		int dir;
		int agrsv;
		int defTime;
		int strtX;
		int strtY;
		int endX;
		int endY;
	};

int main(){
	struct pacman{
		int dir;
		int heart;
		int strtX;
		int strtY;
		int endX;
		int endY;
	};
	int r, c;
	scanf("%d %d", &r, &c);
	int i;
	//1: up, 2: right, 3: down, 4: left
	int ** map = malloc(r * sizeof(int *));
	for(i = 0; i < r; i++)
	{
		map[i] = malloc( c * sizeof(int));
	}
	int j;
	for(i = 0; i < r; i++)
	{
		char line[100];
		scanf("%s", line);
		for(j = 0; j < c; j++)
		{
			map[i][j] = line[j]; 
		}
	}
	int timeM;
	int gameTime;
	int gameScore; //?
	scanf("%d:%d %d", &timeM, &gameTime, &gameScore);
	gameTime += timeM * 60;
	//hatkar khorako tadafoE tahhajomiiiii :)
	struct ghost ghosts[4]; 
	scanf("pacman: %d %d (%d,%d) (%d,%d)", &pacman.dir, &pacman.heart, &pacman.strtX, &pacman.strtY, &pacman.endX, &pacman.endY);
	for(i = 0; i < 4; i++)
	{
		scanf("%*s %d %d", &ghosts[i].dir, &ghosts[i].agrsv);
		if(ghosts[i].agrsv)
		{
			ghosts[i].defTime = 0;
		}
		else
		{
			scanf("%d", &ghosts[i].defTime);
		}
		scanf("(%d,%d) (%d,%d)", &ghosts[i].strtX, &ghosts[i].strtY, &ghosts[i].endX, &ghosts[i].endY);
	}
}
