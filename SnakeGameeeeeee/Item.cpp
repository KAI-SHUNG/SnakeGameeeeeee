#include "Item.h"
#include <stdlib.h>
#include <time.h>

Item::Item(int unitx, int unity)
	:UNITX(unitx), UNITY(unity), x(-1), y(-1),exist(false),counter(0)
{
	srand((unsigned)time(0));
}
void Item::create(std::vector<Coordinate> snake, int not_x, int not_y)
{
	bool check;
	do
	{
		check = 1;
		x = rand() % UNITX;
		y = rand() % UNITY;
		for (auto it = snake.begin(); it != snake.end(); ++it)
		{
			if ((*it).X == x && (*it).Y == y)
			{
				check = 0;
				break;
			}
		}
		if (not_x == x && not_y == y)
		{
			check = 0;
			continue;
		}
	} while (!check);
}
void Item::reset()
{
	x = -1;
	y = -1;
	exist = false;
}
int Item::get_x()
{
	return x;
}
int Item::get_y()
{
	return y;
}