#include "Timer.h"
#include <time.h>

clock_t goldApple_create;
clock_t frame_start;

Timer::Timer()
{

}
void Timer::frameStart()
{
	frame_start = clock();
}
int Timer::frameTime()
{
	return clock() - frame_start;
}

void Timer::goldAppleCreate()
{
	goldApple_create = clock();
}
int Timer::goldAppleTime()
{
	return clock() - goldApple_create;
}

int Timer::getTime()
{
	return clock();
}