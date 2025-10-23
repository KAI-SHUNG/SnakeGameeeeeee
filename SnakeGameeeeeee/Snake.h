#pragma once

#define ATTENTION "注意，蛇死亡判定未来需要更新墙的坐标，可能需要新的接口"
class Snake
{
private:
	int UnitX;
	int UnitY;
	int molX(int x);
	int molY(int y);
public:
	Snake(int unitX, int unitY);				//构造函数，创建数组，初始化蛇
	~Snake();									//析构函数，释放new

	//更新蛇头下一刻坐标
	void snakeHeadNextTick(char dir);
	//蛇死亡判定，死亡返回true
	bool death();
	//蛇生长与移动，输入苹果坐标，苹果被吃返回true
	bool growAndMove(int xapple, int yapple);

	//读取蛇长的接口
	const int SnakeLength();
	//读取坐标的接口
	const int* SnakeX();
	//读取坐标的接口
	const int* SnakeY();
	//读取坐标的接口
	const char* SnakeDir();
};