#pragma once
#define ATTENTION "注意，蛇死亡判定未来需要更新墙的坐标，可能需要新的接口"

struct Coordinate {
	int X;
	int Y;
	char Dir;
};

class Snake
{
private:
	int UnitX;
	int UnitY;
	std::vector<Coordinate> coordinate;
	//让蛇坐标循环，取mol
	int molX(int x); int molY(int y);

public:
	Snake(int unitX, int unitY);				//构造函数，创建数组，初始化蛇
	~Snake();									//析构函数，释放new

	//更新蛇头下一刻坐标
	void snakeHeadNextTick(char dir);
	//蛇死亡判定，死亡返回true
	bool death();
	//输入苹果坐标，苹果被吃返回true
	bool eatApple(int xapple, int yapple);
	//输入金苹果坐标，金苹果被吃返回true
	bool eatGoldApple(int xapple, int yapple);
	//蛇移动
	void move();

	std::vector<Coordinate> coordinate_p();
	//std::vector<Coordinate> coordinate_p();
	//读取蛇长的接口
	const int SnakeLength() const;
	//读取坐标的接口
	const int* SnakeX() const;
	//读取坐标的接口
	const int* SnakeY() const;
	//读取朝向的接口
	const char* SnakeDir() const;
};