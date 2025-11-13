#pragma once
#define ATTENTION "注意，蛇死亡判定未来需要更新墙的坐标，可能需要新的接口"
#include <vector>
#include "Coordinate.h"

class Snake
{
private:
	int UNITX;
	int UNITY;
	Coordinate coord_next;//下一刻坐标
	bool eat_apple = false;
	std::vector<Coordinate> coordinate;//坐标

	//让蛇坐标循环，取mol
	int molX(int x);
	int molY(int y);
public:
	Snake(int unitx, int unity);		//构造函数，初始化蛇
	~Snake();

	void snakeHeadNextTick(char dir);	//更新蛇头下一刻坐标
	bool death();						//死亡判定，死亡返回true
	bool eatApple(int x, int y);		//输入苹果坐标，苹果被吃返回true
	bool eatGoldApple(int x, int y);	//输入金苹果坐标，金苹果被吃返回true
	void move();						//蛇移动
	std::vector<Coordinate> coordinate_p();//返回蛇坐标in vector
};