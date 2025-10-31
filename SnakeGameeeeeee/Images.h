#pragma once

class Images
{
public:
	Images(int unitx, int unity);
	void gameInit();

	void placeSnake(const int* snakeX, const int* snakeY, const char* snakeDir, int snakeLength);
	void placeApple(int x, int y);
	void placeGoldApple(int x, int y);
	void placeButton(int x, int y);
	void placeButtonPressed(int x, int y);
	void placeSoundOn(int x, int y);
	void placeSoundOff(int x, int y);
	void placeWall(int x, int y);
	void placeTitle(int x, int y);
	void placePause(double x, double y);
	void placeBoard(int score);

	void flushBegin();
	void flushEnd();

	void test();

private:
	void snakeHead(int x, int y, char dir);
	void snakeBody(int x, int y, char dir0, char dir1);
	void snakeTail(int x, int y, char dir);

	const int UnitX;
	const int UnitY;
};
