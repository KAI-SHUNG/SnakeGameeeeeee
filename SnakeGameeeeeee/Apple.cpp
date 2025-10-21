#include <stdlib.h>
#include <time.h>
#include "Apple.h"

Apple::Apple(int unitx, int unity)
	:UnitX(unitx), UnitY(unity), appleX(0), appleY(0)
{

}

void Apple::createApple(const int* x, const int* y, int length)
{
	int check;
	do
	{
		srand((unsigned)time(0));
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

const int Apple::AppleX()
{
	return appleX;
}

const int Apple::AppleY()
{
	return appleY;
}