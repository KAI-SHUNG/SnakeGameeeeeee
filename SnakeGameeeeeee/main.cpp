/*
可以考虑添加更多趣味道具、穿墙、加速减速等等，
更重要的是程序的结构设计不能有太多冗余、重复的代码、要使用函数、类等方法实现代码的复用，
还有界面和游戏逻辑的解耦合，就是换一种图形库，也能很好的利用原有的游戏逻辑
EasyX
*/

/*
class道具（加速减速，闪现，技能键，护盾……
墙壁？随机生成？
排行榜，记录成绩……

*/

//实现功能：
//1.最右端传送（简单）^^^
//2.！！！蛇身蛇头蛇尾，转弯处？画图？？ ^^^
//3.
//4.生成道具，护盾
//5.地图，有不同wall
//6.
//7.计时器，指定时间后道具/果实消失 ^^^
//8.图形界面，排行榜

//分离,解耦合!!
//如果未来客户要换一个图形库,你的代码怎么复用??
//game游戏逻辑和images图形分离
//你要写一个道具类，还是苹果类，金苹果类，加速类……？

//下一步				计分板 ^^^
//下下下一步			金苹果的加入：^^^
//						吃六个苹果生成金苹果 ^^^ ，在sweet moment吃到金苹果下一次变为吃三个苹果就生成金苹果 ^^^
//							仿照高中诺基亚的逻辑，倒计时6秒，加分递减，sweet moment: 5 ^^^
//							加一个进度条，可以倒计时 ^^^
//下下一步			menu界面 ^^^ ，再来一局的重置 ^^^ ，难度选择 ， 鼠标控制的加入
//下下下下一步		menu排行榜、存档
//下下下下下一步		声音控制功能
//下下下下下下一步	不同地图

#include <Windows.h>
#include <iostream>
#include <vector>
#include "Images.h"
#include "Keyboard.h"
#include "Music.h"
#include "Timer.h"
#include "Snake.h"
#include "Apple.h"

#define MENUX 24			//菜单界面X共24单元格
#define MENUY 20			//菜单界面Y共20单元格

#define UNITX 16			//游戏界面X共16单元格
#define UNITY 20			//游戏界面Y共20单元格
#define TICK_EASY 250		//简单模式帧时长250ms
#define TICK_NORMAL 150		//普通模式帧时长150ms
#define TICK_HARD 100		//困难模式帧时长100ms
#define TIME_TOTAL 6000		//金苹果存在时间6000ms
#define POINT_APPLE 1		//苹果分值
#define POINT_GOLDAPPLE 26	//金苹果分值

int appleX;
int appleY;
int goldAppleX;
int goldAppleY;
void placeSnake(std::vector<Coordinate>);
void createApple(std::vector<Coordinate>);
void createGoldApple(std::vector<Coordinate>);

Images image(MENUX, MENUY,UNITX, UNITY);
Keyboard keyboard;
Music music;

int resourceCheck();
int loadFont();
MenuState Menu(MenuState&);
void Sound();
int Game();
GameoverState Gameover();

int main()
{
	if (resourceCheck() != 0)
	{
		system("pause");
		return 1;
	}
	MenuState menuState = MenuState::PLAY;
	while(1)
	{
		Menu(menuState);
		switch (menuState)
		{
		case(MenuState::PLAY):
			music.menuStop();
			do{
				int score = Game();
				if (score == -1)
				{
					break;
				}
				Sleep(500);
			} while (Gameover() != GameoverState::EXIT);
			break;
		case(MenuState::EXIT):
			return 0;
		}
		Sleep(TICK_NORMAL);
	}
}

int resourceCheck()
{
	return image.loadImages() + loadFont() + music.loadMusic();
}
MenuState Menu(MenuState& state)
{
	image.menuInit();
	music.menu();
	Timer timer;
	while (1)
	{
		if (keyboard.enter())
		{
			return state;
		}
		if (state == MenuState::EXIT && keyboard.escape())
		{
			return state;
		}
		keyboard.menu(state);

		image.flushBegin();
		image.placePlay(MENUX / 2, 12, state == MenuState::PLAY);
		image.placeExit(MENUX / 2, 15, state == MenuState::EXIT);
		image.placeTitle(timer.getTime());
		image.flushEnd();
		Sleep(TICK_NORMAL);
	}
}
void Sound()
{
	while (1)
	{
		image.flushBegin();
		//image.placeSound(UNITX / 2 - 2, UNITY / 2 - 2, 1);
		//image.placeSound(UNITX / 2 - 2, UNITY / 2 - 2, 1);
		image.flushEnd();
	}
}
int Game()
{
	//初始化
	//Apple apple(UNITX, UNITY);
	Snake snake(UNITX, UNITY);
	Timer timer;
	appleX = appleY = goldAppleX = goldAppleY = -1;
	int apple_counter = 0;
	image.gameInit();
	music.game();
	bool appleExist = false;
	bool goldAppleExist = false;
	int score = 0;
	int tick = TICK_HARD;//未来难度选择
	//游戏主体
	while (1)
	{
		//不知道哪里有问题，好几次蛇突然不动了 
		//莫名其妙的bug(*_*)(*_*)(*_*)(*_*)(*_*)(*_*)
		//给你👻辣，给你上香
		//好像好久没出现了？ 2025/11/7
		/* --------------------------------
						***
						|||
						|||
					———————————
					\		  /
					 \_______/
		---------------------------------*/
		//帧率控制
		timer.frameStart();
		// 暂停 && 退出
		if (keyboard.space() || keyboard.escape())
		{
			music.click();
			music.gamePause();
			// 中间显示暂停界面，之后需要分支，resume或者exit
			do {
				image.placePause(UNITX / 2 - 2, UNITY / 2 - 3);//显示暂停
				Sleep(250);//这一句好像很关键，删了不行
				if (keyboard.space())
				{
					music.click();
					break;//继续游戏
				}//（已解决）为何只有第一次对，bugbugbug(*_*)(*_*)(*_*)(*_*)
				if (keyboard.escape())
				{
					music.gameStop();
					return -1;//退出
				}
			} while (1);
			music.gameResume();
			//暂停之后tick - framtime 让Sleep的时间为负数，所以一直停住，刷新start即可解决
			timer.frameStart();
		}
		//wasd控制
		/*
		我真是天才
		先定义为上一个dir，有修改就改了，没修改按原来
		省去了再写一个读取Dir[0]的函数
		*/
		char dir = *snake.SnakeDir();
		keyboard.move(dir);
		//更新蛇头下一刻坐标
		snake.snakeHeadNextTick(dir);
		//死亡判定
		if (snake.death())
		{
			image.temp();
			music.death();
			music.gameStop();
			return score;
		}
		//判定金苹果存在是否超时
		int goldAppleTime = timer.goldAppleTime();
		if (goldAppleTime > TIME_TOTAL)
		{
			goldAppleExist = false;
		}
		//判定是否吃到苹果 && 金苹果 && 蛇生长
		if (snake.eatApple(appleX, appleY))
		{
			music.eat();
			score += POINT_APPLE;
			apple_counter += 1;
			appleExist = false;
		}else 
		if (goldAppleExist && snake.eatGoldApple(goldAppleX, goldAppleY))
		{
			music.bell();
			music.eat();
			score += POINT_GOLDAPPLE * (TIME_TOTAL - goldAppleTime) / TIME_TOTAL;
			if (goldAppleTime / 1000 == 1)
			{
				apple_counter += 3;
			}
			goldAppleExist = false;
		}
		//蛇的移动
		snake.move();
		//生成苹果 && 生成金苹果
		if (!appleExist)
		{
			createApple(snake.coordinate_p());
			appleExist = true;
			if (apple_counter % 6 == 0 && !goldAppleExist && apple_counter != 0)
			{
				createGoldApple(snake.coordinate_p());
				goldAppleExist = true;
				timer.goldAppleCreate();
			}
		}
		//图像输出
		image.flushBegin();
		if (goldAppleExist)
		{
			image.placeBar(goldAppleTime, TIME_TOTAL);
			image.placeGoldApple(goldAppleX, goldAppleY);
		}
		image.placeApple(appleX, appleY);
		image.placeBoard(score);
		image.placeSnake(snake.SnakeX(), snake.SnakeY(), snake.SnakeDir(), snake.SnakeLength());
		image.flushEnd();
		//帧率控制
		Sleep(tick - timer.frameTime());
	}
}
GameoverState Gameover()
{
	GameoverState state = GameoverState::AGAIN;
	while (1)
	{
		if (keyboard.enter())
		{
			return state;
		}
		if (keyboard.escape() && state == GameoverState::EXIT)
		{
			return state;
		}
		keyboard.gameover(state);

		image.flushBegin();
		image.tempDisplay();
		image.placeAgain(UNITX / 2, 10, state == GameoverState::AGAIN);
		image.placeExit(UNITX / 2, 13, state == GameoverState::EXIT);
		image.flushEnd();
		Sleep(TICK_NORMAL);
	}
}
int loadFont()
{
	LPCSTR ROG_Fonts_Path = "./Resource/ROG_Fonts.otf";
	int addFontResult = AddFontResourceExA(ROG_Fonts_Path, FR_PRIVATE, 0);
	if (addFontResult > 0)
	{
		SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
		return 0;
	}
	else
	{
		std::cerr << "Font Resource ERROR!\n";
		return 1;
	}
}

void placeSnake(std::vector<Coordinate> coord)
{
	image.snakeHead(coord.at(0).X, coord.at(0).Y, coord.at(0).Dir);
	for (int i = 1; i < coord.size(); ++i)
	{
		image.snakeBody(coord.at(i).X, coord.at(i).Y,
			coord.at(i).Dir, coord.at(i - 1).Dir);
		//注意这里反直觉，方向靠近蛇头的为下一个，但是是i - 1
	}
	image.snakeTail(coord.at(coord.size() - 1).X,
		coord.at(coord.size() - 1).Y,
		coord.at(coord.size() - 2).Dir);
	//注意这里snakeTial读取的应该是length-2的Dir
}
void createApple(std::vector<Coordinate> coord)
{
	bool check;
	do
	{
		check = 1;
		appleX = rand() % UNITX;
		appleY = rand() % UNITY;
		for (int i = 0; i < coord.size(); ++i)
		{
			if (coord.at(i).X == goldAppleX && coord.at(i).Y == goldAppleY)
			{
				check = 0;
				break;
			}
		}
	} while (!check);
}
void createGoldApple(std::vector<Coordinate> coord)
{
	bool check;
	do
	{
		check = 1;
		goldAppleX = rand() % UNITX;
		goldAppleY = rand() % UNITY;
		for (int i = 0; i < coord.size(); ++i)
		{
			if (coord.at(i).X == goldAppleX && coord.at(i).Y == goldAppleY)
			{
				check = 0;
				break;
			}
		}
		if (goldAppleX == appleX && goldAppleY == appleY)
		{
			check = 0;
			continue;
		}
	} while (!check);
}