#include "Snake.h"
#include <iostream>
#include <vector>

std::vector<Coordinate> coordinate;
bool eat_apple = false;

//int* snakeX;		//声明蛇身坐标的指针
//int* snakeY;		//声明蛇身坐标的指针
//char* snakeDir;		//声明蛇身朝向的指针
//int length;
int snakeXNext;		//声明蛇头下一刻坐标
int snakeYNext;		//声明蛇头下一刻坐标
char snakeDirNext;	//声明蛇头下一刻朝向

//便于修改蛇身坐标
//void setSnakePosition(int position, int x1, int y1, char dir1)
//{
//	snakeX[position] = x1;
//	snakeY[position] = y1;
//	snakeDir[position] = dir1;
//}
//构造函数，创建数组，初始化蛇
Snake::Snake(int unitX, int unitY)
	:UnitX(unitX), UnitY(unitY)
{
	//因为长度未定，需要动态数组new
	//snakeX = new int[UnitX * UnitY]();
	//snakeY = new int[UnitX * UnitY]();
	//snakeDir = new char[UnitX * UnitY]();
	//setSnakePosition(0, UnitX / 2, UnitY / 2, 'd');
	//setSnakePosition(1, UnitX / 2 - 1, UnitY / 2, 'd');
	//length = 2;
	coordinate.push_back({ UnitX / 2 - 1, UnitY / 2, 'd' });
	coordinate.push_back({ UnitX / 2, UnitY / 2, 'd' });
	//测试代码
	//length = 8;
	//setSnakePosition(0, 3, 1, 'w');
	//setSnakePosition(1, 3, 2, 'w');
	//setSnakePosition(2, 2, 2, 'd');
	//setSnakePosition(3, 2, 1, 's');
	//setSnakePosition(4, 2, 0, 's');
	//setSnakePosition(5, 1, 0, 'd');
	//setSnakePosition(6, 0, 0, 'd');
	//setSnakePosition(7, 0, 1, 'w');
}

//析构函数，释放new
Snake::~Snake()
{
	//delete[] snakeX; snakeY, snakeDir;
}

int Snake::molX(int x)
{
	if (x < 0)
	{
		x += UnitX;
	}
	return x % UnitX;
}
int Snake::molY(int y)
{
	if (y < 0)
	{
		y += UnitY;
	}
	return y % UnitY;
}

void Snake::snakeHeadNextTick(char dir)
{
	switch (dir)
	{
	case('w'):snakeXNext = molX(coordinate.at(0).X);	snakeYNext = molY(coordinate.at(0).Y - 1);	break;
	case('a'):snakeXNext = molX(coordinate.at(0).X - 1);snakeYNext = molY(coordinate.at(0).Y);		break;
	case('s'):snakeXNext = molX(coordinate.at(0).X);	snakeYNext = molY(coordinate.at(0).Y + 1);	break;
	case('d'):snakeXNext = molX(coordinate.at(0).X + 1);snakeYNext = molY(coordinate.at(0).Y);		break;
	}
	snakeDirNext = dir;
}

bool Snake::death()
{
	for (int i = 0; i < coordinate.size(); ++i)
	//for (int i = 0; i < length; ++i)//两个版本，length在将要吃蛇尾的时候判定死亡
	//for (int i = 0; i < length - 1; ++i)//length - 1在将要吃到蛇尾时不判定死亡---两格长可以原地掉头
	{
		//if (snakeXNext == snakeX[i] && snakeYNext == snakeY[i])
		if (snakeXNext == coordinate.at(i).X && snakeYNext == coordinate.at(i).Y)
		{
			return true;
		}
	}
	return false;
}

bool Snake::eatApple(int xapple, int yapple)
{
	//一个自认为精妙的地方，如果length++，能保证蛇尾坐标给[length]
	//如果length不变，可以保证蛇尾被舍弃
	if (snakeXNext == xapple && snakeYNext == yapple)
	{
		//length++;
		eat_apple = true;
		return true;
	}
	return false;
}
bool Snake::eatGoldApple(int xapple, int yapple)
{
	if (snakeXNext == xapple && snakeYNext == yapple)
	{
		return true;
	}
	return false;
}

void Snake::move()
{
	coordinate.insert(coordinate.begin(), {snakeXNext, snakeYNext, snakeDirNext});
	if (!eat_apple)
	{
		coordinate.pop_back();
		eat_apple = false;
	}
	//for (int i = length - 1; i > 0; --i)
	//{
	//	setSnakePosition(i, snakeX[i - 1], snakeY[i - 1], snakeDir[i - 1]);
	//}
	//setSnakePosition(0, snakeXNext, snakeYNext, snakeDirNext);
}

std::vector<Coordinate> Snake::coordinate_p()
{
	return coordinate;
}


//const int Snake::SnakeLength() const
//{
//	return length;
//}
//const int* Snake::SnakeX() const
//{
//	return snakeX;
//}
//const int* Snake::SnakeY() const
//{
//	return snakeY;
//}
//const char* Snake::SnakeDir() const
//{
//	return snakeDir;
//}