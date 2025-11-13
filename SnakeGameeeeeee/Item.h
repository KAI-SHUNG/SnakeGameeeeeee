#pragma once
#include "Coordinate.h"
#include <vector>
class Item
{
public:
	Item(int unitx, int unity);
	void create(std::vector<Coordinate> snake, int not_x, int not_y);
	void reset();
	int get_x();
	int get_y();
	bool exist;
	int counter;
private:
	int UNITX;
	int UNITY;
	int x;
	int y;
};