#include "Item.h"
#include <stdlib.h>
#include <time.h>
#define UNIT 10
#define BOARD 2
Item::Item(int unitx, int unity, IMAGE* img)
	:Img(img), x(-1), y(-1), exist(false), counter(0)
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
void Item::display()
{
	int w = Img->getwidth();
	int h = Img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT, (BOARD + y) * UNIT, w, h,
		GetImageHDC(Img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
const int Item::get_x() const
{
	return x;
}
const int Item::get_y() const
{
	return y;
}