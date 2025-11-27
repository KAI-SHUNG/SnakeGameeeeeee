#pragma once
#include <time.h>

class Timer
{
private:
public:
	Timer();
	void frameStart();
	int frameTime();
	void goldAppleCreate();
	int goldAppleTime();
	int getTime();
};