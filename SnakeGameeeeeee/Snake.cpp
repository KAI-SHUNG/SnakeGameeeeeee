#include "Snake.h"
Snake::Snake(int unitx, int unity)
	:coord_next({unitx / 2 + 1, unity / 2, 'd'})
{
	coordinate.push_back({ UNITX / 2, UNITY / 2, 'd' });
	coordinate.push_back({ UNITX / 2 - 1, UNITY / 2, 'd' });
}

void Snake::snakeHeadNextTick(char dir)
{
	switch (dir)
	{
	case('w'):coord_next = {molX(coordinate.at(0).X),		molY(coordinate.at(0).Y - 1),dir };	break;
	case('a'):coord_next = {molX(coordinate.at(0).X - 1),	molY(coordinate.at(0).Y)	,dir};	break;
	case('s'):coord_next = {molX(coordinate.at(0).X),		molY(coordinate.at(0).Y + 1),dir};	break;
	case('d'):coord_next = {molX(coordinate.at(0).X + 1),	molY(coordinate.at(0).Y)	,dir};	break;
	}
}

bool Snake::death()
{
	for (int i = 0; i < coordinate.size(); ++i)
	{
		if (coord_next.X == coordinate.at(i).X && coord_next.Y == coordinate.at(i).Y)
		{
			return true;
		}
	}
	return false;
}

bool Snake::eatApple(int x, int y)
{
	if (coord_next.X == x && coord_next.Y == y)
	{
		eat_apple = true;
		return true;
	}
	return false;
}
bool Snake::eatGoldApple(int x, int y)
{
	return coord_next.X == x && coord_next.Y == y;
}

void Snake::move()
{
	coordinate.insert(coordinate.begin(), coord_next);
	if (!eat_apple)
	{
		coordinate.erase(coordinate.end() - 1);
	}
	eat_apple = false;
}

std::vector<Coordinate> Snake::coord() { return coordinate; }
int Snake::molX(int x) { return (x + UNITX) % UNITX; }
int Snake::molY(int y) { return (y + UNITY) % UNITY; }