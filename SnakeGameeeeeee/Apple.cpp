#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Apple.h"

Apple::Apple(int unitx, int unity)
	:UNITX(unitx), UNITY(unity), x(-1), y(-1),counter(0)
{
	srand((unsigned)time(0));
}

//void Apple::create(const int* x, const int* y, int length)
//{
//	bool check;
//	do
//	{
//		check = 1;
//		appleX = rand() % UNITX;
//		appleY = rand() % UNITY;
//		for (int i = 0; i < length; ++i)
//		{
//			if (*(x + i) == appleX && *(y + i) == appleY)
//			{
//				check = 0;
//				break;
//			}
//		}
//	} while (!check);
//}


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