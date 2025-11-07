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
//7.计时器，指定时间后道具/果实消失
//8.图形界面，排行榜

//分离,解耦合!!
//如果未来客户要换一个图形库,你的代码怎么复用??
//game游戏逻辑和images图形分离
//你要写一个道具类，还是苹果类，金苹果类，加速类……？

//下一步				计分板 ^^^
// 
//下下下一步			金苹果的加入：^^^
//						吃六个苹果生成金苹果 ^^^ ，在sweet moment吃到金苹果下一次变为吃三个苹果就生成金苹果 ^^^
//							仿照高中诺基亚的逻辑，倒计时6秒，加分递减，sweet moment: 5 ^^^
//							加一个进度条，可以倒计时 ^^^
//下下一步			menu界面，鼠标控制的加入，再来一局的重置
//下下下下一步		排行榜、存档
//下下下下下一步		声音控制功能
//下下下下下下一步	不同地图

//#include <easyx.h>
#include <time.h>
#include <Windows.h>
#include <wingdi.h>
#include "Images.h"
#include "Keyboard.h"
#include "Music.h"
#include "Timer.h"
#include "Snake.h"
#include "Apple.h"
#define MENUX 24
#define MENUY 20
#define XUNIT 16//X共16单元格
#define YUNIT 20//Y共20单元格
#define TICK_EASY 250	//帧时长250ms
#define TICK_NORMAL 150	//帧时长150ms
#define TICK_HARD 100	//帧时长100ms
#define TIME_TOTAL 6000	//金苹果存在时间6000ms
extern Menu;

int resourceCheck();
Menu menu(Images&, Keyboard&, Music&);
void game(Images&, Keyboard&, Music&);

int main()
{
	Images image(XUNIT, YUNIT);
	Music music;
	Keyboard keyboard;
	Menu menuState;
	while (1)
	{
		menuState = menu(image, keyboard, music);
		switch (menuState)
		{
		case(Menu::BEGIN):
			music.menuStop();
			game(image, keyboard, music); break;
		case(Menu::EXIT):return 0;
		}
		Sleep(200);
	}
	//menu(image, keyboard, music);
	//game(image, keyboard, music);
	//Sleep(1000);
	return 0;
}

int resourceCheck()
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
		return -1;
	}
}

Menu menu(Images& image, Keyboard& keyboard, Music& music)
{
	image.menuInit();
	music.menu();
	Menu state = BEGIN;
	while (1)
	{
		keyboard.flush();
		keyboard.menu(state);
		//if (keyboard.menu(state))
		if(keyboard.enter())
		{
			return state;
		}

		image.flushBegin();
		image.placeButton(MENUX / 2, 10, state == Menu::BEGIN);
		image.placeButton(MENUX / 2, 14, state == Menu::EXIT);
		image.placeTitle(clock());
		image.flushEnd();
		Sleep(160);
	}
}

void game(Images& image, Keyboard& keyboard, Music& music)
{
	//初始化
	Snake snake(XUNIT, YUNIT);
	Apple apple(XUNIT, YUNIT);
	Timer timer;
	image.gameInit();
	music.game();
	music.musicOn();
	//游戏主体
	apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());
	bool appleExist = true;
	bool goldAppleExist = false;
	int goldApplePoint = 28;
	int applePoint = 1;
	int point = 0;
	int tick = TICK_HARD;//未来难度选择
	while (1)
	{
		//不知道哪里有问题，好几次蛇突然不动了 
		//莫名其妙的bug(*_*)(*_*)(*_*)(*_*)(*_*)(*_*)
		//给你烧香
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
	
		//wasd控制 && 暂停 && 退出
		char dir = *snake.SnakeDir();
		//我真是天才
		//先定义为上一个dir，有修改就改了，没修改按原来
		//省去了再写一个读取Dir[0]的函数
		if (keyboard.game(dir))
		{
			int resume = 0;
			music.gamePause();
			music.click();
			// 中间显示暂停界面，之后需要分支，resume或者exit
			do {
				Sleep(TICK_HARD);//这一句好像很关键，删了不行
				image.placePause(XUNIT / 2 - 2, YUNIT / 2 - 3);//显示暂停
				keyboard.flush();//清空缓冲区，用处不明
				if (keyboard.space())
				{
					music.click();
					break;//继续游戏
				}//（已解决）为何只有第一次对，bugbugbug(*_*)(*_*)(*_*)(*_*)
				if (keyboard.escape())
				{
					music.gameStop();
					return;//退出
				}
			} while (1);
			music.gameResume();
			//暂停之后tick - framtime 让Sleep的时间为负数，所以一直停住，刷新start即可解决
			timer.frameStart();
		}

		//死亡判定
		snake.snakeHeadNextTick(dir);//更新蛇头坐标
		if (snake.death())
		{
			music.gameStop();
			music.death();
			Sleep(1000);
			return;
		}
		//蛇的移动 && 吃苹果 && 吃金苹果
		int goldAppleTime = timer.goldAppleTime();
		if (goldAppleTime > TIME_TOTAL)//判定金苹果存在是否超时
		{
			goldAppleExist = false;
		}
		if (snake.eatApple(apple.AppleX(), apple.AppleY()))//判定是否吃到苹果
		{
			music.eat();
			point += applePoint;
			apple.counter += 1;
			appleExist = false;
		}
		else if (goldAppleExist && snake.eatGoldApple(apple.GoldAppleX(), apple.GoldAppleY()))
			{
				music.eat();
				music.bell();
				point += goldApplePoint * (TIME_TOTAL - goldAppleTime) / TIME_TOTAL;
				if (goldAppleTime / 1000 == 1)
				{
					apple.counter += 3;
				}
				goldAppleExist = false;
			}
		snake.move();
		//生成苹果 && 生成金苹果
		if (!appleExist)
		{
			apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());//生成苹果
			appleExist = true;
			if (apple.counter % 6 == 0 && !goldAppleExist)
			{
				apple.createGoldApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());
				goldAppleExist = true;
				timer.goldAppleCreate();
			}
		}
	
		//图像输出
		image.flushBegin();
		if (goldAppleExist)
		{
			image.placeGoldApple(apple.GoldAppleX(), apple.GoldAppleY());
			image.placeBar(goldAppleTime, TIME_TOTAL);
		}
		image.placeSnake(snake.SnakeX(), snake.SnakeY(), snake.SnakeDir(), snake.SnakeLength());
		image.placeApple(apple.AppleX(), apple.AppleY());
		image.placeBoard(point);
		image.flushEnd();
	
		//帧率控制
		Sleep(tick - timer.frameTime());
	}
}
