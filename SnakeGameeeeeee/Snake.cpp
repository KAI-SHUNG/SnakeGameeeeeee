#include "Snake.h"

int* snakeX;		//声明蛇身坐标的指针
int* snakeY;		//声明蛇身坐标的指针
char* snakeDir;		//声明蛇身坐标的指针
int snakeXNext;		//声明蛇头下一刻坐标
int snakeYNext;		//声明蛇头下一刻坐标
char snakeDirNext;	//声明蛇头下一刻坐标
int length;

//便于修改蛇身坐标
void setSnakePosition(int position, int x1, int y1, char dir1)
{
	snakeX[position] = x1;
	snakeY[position] = y1;
	snakeDir[position] = dir1;
}

//构造函数，创建数组，初始化蛇
Snake::Snake(int x, int y)
	:UnitX(x), UnitY(y)
{
	//因为长度未定，需要动态数组new
	snakeX = new int[UnitX * UnitY]();
	snakeY = new int[UnitX * UnitY]();
	snakeDir = new char[UnitX * UnitY]();
	setSnakePosition(0, UnitX / 2, UnitY / 2, 'd');
	setSnakePosition(1, UnitX / 2 - 1, UnitY / 2, 'd');
	length = 2;

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
	delete[] snakeX; snakeY, snakeDir;
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
//更新蛇头下一刻坐标
void Snake::snakeHeadNextTick(char dir)
{
	switch (dir)
	{
	case('w'):snakeXNext = molX(snakeX[0]);		snakeYNext = molY(snakeY[0] - 1);	break;
	case('a'):snakeXNext = molX(snakeX[0] - 1); snakeYNext = molY(snakeY[0]);		break;
	case('s'):snakeXNext = molX(snakeX[0]);		snakeYNext = molY(snakeY[0] + 1);	break;
	case('d'):snakeXNext = molX(snakeX[0] + 1); snakeYNext = molY(snakeY[0]);		break;
	}
	snakeDirNext = dir;
}

//蛇死亡判定，死亡返回true
bool Snake::death()
{
	for (int i = 0; i < length; ++i)
	{
		if (snakeXNext == snakeX[i] && snakeYNext == snakeY[i])
		{
			return true;
		}
	}
	return false;
}

//蛇生长与移动，输入苹果坐标，苹果被吃返回true
bool Snake::growAndMove(int xapple, int yapple)
{
	int appleeaten = 0;
	if (snakeXNext == xapple && snakeYNext == yapple)
	{
		length++;
		appleeaten = 1;
	}
	//一个自认为精妙的地方，如果length++，能保证蛇尾坐标给[length]
	//如果length不变，可以保证蛇尾被舍弃
	for (int i = length - 1; i > 0; --i)
	{
		setSnakePosition(i, snakeX[i - 1], snakeY[i - 1], snakeDir[i - 1]);
	}
	setSnakePosition(0, snakeXNext, snakeYNext, snakeDirNext);
	return appleeaten;
}

const int Snake::SnakeLength()
{
	return length;
}
const int* Snake::SnakeX()
{
	return snakeX;
}
const int* Snake::SnakeY()
{
	return snakeY;
}
const char* Snake::SnakeDir()
{
	return snakeDir;
}