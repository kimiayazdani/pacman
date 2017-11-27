#include <stdio.h>
int nextMove(int, int, int **, int, int);
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
	struct pacmanS{
		//dir -> 1: up, 2: right, 3: down, 4: left
		int dir;
		int heart;
		int strtX;
		int strtY;
		int endX;
		int endY;
	};
	struct pacmanS pacman;
int main(){
	int leftFood = 0;
	int r, c;
	scanf("%d %d", &r, &c);
	int i;
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
			if(map[i][j] == 'O' || map[i][j] == '*')
				leftFood++;
		}
	}
	int timeM;
	int gameTime;
	int gameScore;
	scanf("%d:%d %d", &timeM, &gameTime, &gameScore);
	gameTime += timeM * 60;
	struct ghost ghosts[4]; 
	scanf("%*s %d %d (%d,%d) (%d,%d)", &pacman.dir, &pacman.heart, &pacman.strtX, &pacman.strtY, &pacman.endX, &pacman.endY);
	for(i = 0; i < 4; i++)
	{
		scanf("%*s %d %d ", &ghosts[i].dir, &ghosts[i].agrsv);
		if(ghosts[i].agrsv)
		{
			ghosts[i].defTime = 0;
		}
		else
		{
			scanf("%d ", &ghosts[i].defTime);
		}
		scanf("(%d,%d) (%d,%d)\n", &ghosts[i].strtX, &ghosts[i].strtY, &ghosts[i].endX, &ghosts[i].endY);
	}
	int mve = nextMove(r, c, map, pacman.endX, pacman.endY);
	pacman.endX = mve / 1000;
	pacman.endY = mve % 1000;
	if(map[pacman.endX][pacman.endY] == 'O')
	{
		for(i = 0; i < 4; i++)
		{
			if(pacman.endX == ghosts[i].endX && pacman.endY == ghosts[i].endY)
			{	
				gameScore += 50;
			}
		}
		--leftFood;
	}
	else
	{
		int eaten = 0;
		if(map[pacman.endX][pacman.endY] == '^')
			gameScore += 20;
		if(map[pacman.endX][pacman.endY] == '*')
		{
			++gameScore;
			--leftFood;
		}	
		for(i = 0; i < 4; i++)
		{
			if(pacman.endX == ghosts[i].endX && pacman.endY == ghosts[i].endY)
			{	
				if(ghosts[i].agrsv)
				{
					--pacman.heart;
					eaten = 1;
				}
				else
				{
					gameScore += 50;
				}
			}
		}	
		if(eaten)
		{
			pacman.endX = pacman.strtX;
			pacman.endY = pacman.strtY;
		}
	}
	printf("(%d,%d)\n%d\n", pacman.endX, pacman.endY, gameScore);
	if(leftFood)
		printf("No");
	else
		printf("Yes");
	
}
int nextMove(int r, int c, int ** map, int x, int y){
	int tempendy = y;
	int tempendx = x;
	if(pacman.dir == 1)
		if(x == 0)
			x = r - 1;
		else
			--x;
	else
		if(pacman.dir == 2)
			if(y == c - 1)
				y = 0;
			else
				++y;
		else
			if(pacman.dir == 3)
				if(x == r - 1)
					x = 0;
				else
					++x;
			else
				if(y == 0)
					y = c - 1;
				else
					--y;
	if(map[x][y] == '#')
	{
		x = tempendx;
		y = tempendy;
	}	
	return x * 1000 + y;
}
/*
5 10
#___**#**#
###**##*##
____****O_
_##_^*#___
#_____#_*#
01:10 27
pacman: 1 3 (2,0) (4,5)
*/
