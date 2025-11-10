#pragma once
#include <iostream>
#include <windows.h>
#include <mmsystem.h>				// 包含mciSendStringA声明
#pragma comment(lib, "winmm.lib")	// 链接必要的库

class Music
{
public:
	Music();
	int loadMusic();
	void menu();
	void menuStop();
	void game();
	void gameStop();
	void gamePause();
	void gameResume();

	void click();
	void eat();
	void bell();
	void death();
	void musicOn();
	void musicOff();
	void soundEffectOn();
	void soundEffectOff();
};