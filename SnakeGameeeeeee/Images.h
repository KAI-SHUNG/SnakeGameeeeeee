#pragma once

class Images
{
public:
	Images(int x, int y);
	void init();
	void test();
	void stage(const int* snakeX, const int* snakeY, const char* snakeDir, int snakeLength,
		int appleX, int appleY);
	void snakeHead(int x, int y, char dir);
	void snakeBody(int x, int y, char dir0, char dir1);
	void snakeTail(int x, int y, char dir);
	void placeApple(int x, int y);
	void placeGoldApple(int x, int y);
	void placeButton(int x, int y);
	void placeButtonPressed(int x, int y);
	void placeSoundOn(int x, int y);
	void placeSoundOff(int x, int y);
	void placeWall(int x, int y);
	void placeTitle(int x, int y);

	void clearUnit(int x, int y);
	void clear();
private:
	const int UnitX;
	const int UnitY;
};
