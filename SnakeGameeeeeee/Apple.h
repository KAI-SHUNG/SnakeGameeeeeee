#pragma once
#include "Coordinate.h"
#include <vector>
class Apple
{
public:
	Apple(int unitx, int unity);
	void create(std::vector<Coordinate> snake, int goldapple_x, int goldapple_y);

	int counter;
	const int AppleX() const;
	const int AppleY() const;
	const int GoldAppleX() const;
	const int GoldAppleY() const;

private:
	int UNITX;
	int UNITY;
	int x;
	int y;
};