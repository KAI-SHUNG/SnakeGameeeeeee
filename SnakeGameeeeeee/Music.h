#pragma once

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