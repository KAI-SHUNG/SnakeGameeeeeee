#include "Music.h"
#include <windows.h>
#include <mmsystem.h>				// 包含mciSendStringA声明
#pragma comment(lib, "winmm.lib")	// 链接必要的库

Music::Music()
{
	mciSendStringA("open ./Resource/Music/menu_bgm.mp3 type mpegvideo alias menubgm", NULL, 0, NULL);
	mciSendStringA("open ./Resource/Music/game_bgm.mp3 type mpegvideo alias gamebgm", NULL, 0, NULL);
	mciSendStringA("open ./Resource/Music/click_sound.mp3 type mpegvideo alias click", NULL, 0, NULL);
	mciSendStringA("open ./Resource/Music/eat_sound.mp3 type mpegvideo alias eat", NULL, 0, NULL);
	mciSendStringA("open ./Resource/Music/death_sound.mp3 type mpegvideo alias death", NULL, 0, NULL);
}

void Music::menu()
{
	mciSendStringA("play menubgm repeat from 0", NULL, 0, NULL);
}

void Music::menuStop()
{
	mciSendStringA("stop menubgm", NULL, 0, NULL);
}

void Music::game()
{
	mciSendStringA("play gamebgm repeat from 0", NULL, 0, NULL);
}

void Music::gameStop()
{
	mciSendStringA("stop gamebgm", NULL, 0, NULL);
}

void Music::gamePause()
{
	mciSendStringA("pause gamebgm", NULL, 0, NULL);
}

void Music::gameResume()
{
	mciSendStringA("resume gamebgm", NULL, 0, NULL);
}


void Music::click()
{
	mciSendStringA("play click from 0", NULL, 0, NULL);
}

void Music::eat()
{
	mciSendStringA("play eat from 0", NULL, 0, NULL);
}

void Music::death()
{
	mciSendStringA("play death from 0", NULL, 0, NULL);
}

void Music::musicOn()
{
	mciSendStringA("setaudio menubgm volume to 500", NULL, 0, NULL);
	mciSendStringA("setaudio gamebgm volume to 300", NULL, 0, NULL);
}

void Music::musicOff()
{
	mciSendStringA("setaudio menubgm volume to 0", NULL, 0, NULL);
	mciSendStringA("setaudio gamebgm volume to 0", NULL, 0, NULL);
}

void Music::soundEffectOn()
{
	mciSendStringA("setaudio click volume to 500", NULL, 0, NULL);
	mciSendStringA("setaudio eat volume to 500", NULL, 0, NULL);
	mciSendStringA("setaudio death volume to 500", NULL, 0, NULL);
}

void Music::soundEffectOff()
{
	mciSendStringA("setaudio click volume to 0", NULL, 0, NULL);
	mciSendStringA("setaudio eat volume to 0", NULL, 0, NULL);
	mciSendStringA("setaudio death volume to 0", NULL, 0, NULL);
}