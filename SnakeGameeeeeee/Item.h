#pragma once
#include "Coordinate.h"
#include <vector>
#include <easyx.h>
class Item
{
public:
	Item(int unitx, int unity, IMAGE* img);
	void create(std::vector<Coordinate> snake, int not_x, int not_y);
	void reset();
	void display();
	const int get_x() const;
	const int get_y() const;
	bool exist;
	int counter;
private:
	IMAGE* i0;
	int UNITX;
	int UNITY;
	int x;
	int y;
};