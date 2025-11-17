#pragma once
#include "Struct.h"
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
	IMAGE* Img;
	int x;
	int y;
};