#pragma once
#define ATTENTION "注意，蛇死亡判定未来需要更新墙的坐标，可能需要新的接口,比如not = vector{int , int }"
#include "Tools.h"

class Snake
{
public:
	Snake(int unitx, int unity);		//构造函数，初始化蛇

	void snakeHeadNextTick(char dir);	//更新蛇头下一刻坐标
	bool death();						//死亡判定，死亡返回true
	bool eatApple(int x, int y);		//输入苹果坐标，苹果被吃返回true
	bool eatGoldApple(int x, int y);	//输入金苹果坐标，金苹果被吃返回true
	void move();						//蛇移动
	const std::vector<Coordinate>& coord();//返回蛇坐标in vector

private:
	bool eat_apple = false;
	Coordinate coord_next;//下一刻坐标
	std::vector<Coordinate> coordinate;//坐标

	//让蛇坐标循环，取mol
	int molX(int x);
	int molY(int y);
};