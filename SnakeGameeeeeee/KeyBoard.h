#pragma once

class KeyBoard
{
public:
	//·µ»Ø1´ú±íÔÝÍ£
	bool getAndPause(char& dir);
	bool resume();
	bool escape();
	void flush();
};