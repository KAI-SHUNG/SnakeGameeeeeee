#pragma once

class Images
{
public:
	Images(int menux, int menuy, int unitx, int unity);
	int loadImages();
	void menuInit();
	void gameInit();

	void placeSnake(const int* snakeX, const int* snakeY, const char* snakeDir, int snakeLength);

	void placeApple(int x, int y);
	void placeGoldApple(int x, int y);

	void placeButton(int x, int y, bool state);
	void placePlay(int x, int y, bool state);
	void placeAgain(int x, int y, bool state);
	void placeExit(int x, int y, bool state);
	//void placeButtonPressed(int x, int y);
	void placeWall(int x, int y);
	void placeTitle(int clock);
	void placePause(int x, int y);
	void placeBoard(int score);
	void placeBar(int time, int time_total);
	void placeSound(int x, int y, bool state);
	//void placeSoundOff(int x, int y);

	void flushBegin();
	void flushEnd();
	void temp();
	void tempDisplay();
	//void test();
private:
	void snakeHead(int x, int y, char dir);
	void snakeBody(int x, int y, char dir0, char dir1);
	void snakeTail(int x, int y, char dir);

	const int MenuX;
	const int MenuY;
	const int UnitX;
	const int UnitY;
};
