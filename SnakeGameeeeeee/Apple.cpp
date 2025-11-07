#include <stdlib.h>
#include <time.h>
#include "Apple.h"


Apple::Apple(int unitx, int unity)
	:UnitX(unitx), UnitY(unity), appleX(-1), appleY(-1),goldAppleX(-1),goldAppleY(-1),counter(0)
{
	srand((unsigned)time(0));
}

void Apple::createApple(const int* x, const int* y, int length)
{
	bool check;
	do
	{
		check = 1;
		appleX = rand() % UnitX;
		appleY = rand() % UnitY;
		for (int i = 0; i < length; ++i)
		{
			if (*(x + i) == appleX && *(y + i) == appleY)
			{
				check = 0;
				break;
			}
		}
	} while (!check);
}

void Apple::createGoldApple(const int* x, const int* y, int length)
{
	bool check;
	do
	{
		check = 1;
		goldAppleX = rand() % UnitX;
		goldAppleY = rand() % UnitY;
		for (int i = 0; i < length; ++i)
		{
			if (*(x + i) == goldAppleX && *(y + i) == goldAppleY)
			{
				check = 0;
				break;
			}
		}
		if (goldAppleX == appleX && goldAppleY == appleY)
		{
			check = 0;
			continue;
		}
	} while (!check);
}

const int Apple::AppleX() const
{
	return appleX;
}

const int Apple::AppleY() const
{
	return appleY;
}

const int Apple::GoldAppleX() const
{
	return goldAppleX;
}

const int Apple::GoldAppleY() const
{
	return goldAppleY;
}