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

/*
实现功能：
1.最右端传送（简单）
2.！！！蛇身蛇头蛇尾，转弯处？画图？？
3.生成不多于2/3个果实，bug：生成在蛇头处
4.生成道具，护盾
5.地图，有不同wall
6.同方向按键加速
7.计时器，指定时间后道具/果实消失
8.图形界面，排行榜


*/
//分离,解耦合!!
//如果未来客户要换一个图形库,你的代码怎么复用??
//game游戏逻辑和images图形分离
#include <time.h>
#include <Windows.h>
#include "Images.h"
#include "Snake.h"
#include "Apple.h"
#include "KeyBoard.h"
#include "Music.h"


#define XUNIT 18//X共18单元格
#define YUNIT 20//Y共20单元格
#define TICK 120

//分数计算以苹果被吃和金苹果被吃计算，或存活时间，其实不需要返回蛇长
KeyBoard key;
Music music;
Images image(XUNIT, YUNIT);

void game(Snake& snake, Apple& apple)
{
	//初始化
	music.game();
	image.init();

	apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());
	while (1)
	{
		clock_t start = clock();
		//我真是天才
		//先定义为上一个dir，有修改就改了，没修改按原来
		//省去了再写一个读取Dir[0]的函数
		char dir = *snake.SnakeDir();
		if (key.getAndPause(dir))
		{
			music.gamePause();
			//MSG msg;
			//
			//while (GetMessage(&msg, NULL, WM_KEYFIRST, WM_KEYLAST))
			//{
			//	TranslateMessage(&msg);
			//	outtextxy(0, 0, msg.message);
			//}
			//
			// 中间显示暂停界面，之后需要分支，resume或者exit

			Sleep(1000);//不能用sleep，因为之后tick-（end-start）让sleep的时间为负数，所以一直停住
			music.gameResume();
			start = clock();//刷新start即可解决
			//pause
		}
		snake.snakeHeadNextTick(dir);
		if (snake.death())
		{
			music.death();
			music.gameStop();
			break;
		}
		if (snake.growAndMove(apple.AppleX(), apple.AppleY()))
		{
			music.eat();
			apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());
			//生成苹果
		}
		image.stage(snake.SnakeX(), snake.SnakeY(), snake.SnakeDir(), snake.SnakeLength(),
			apple.AppleX(), apple.AppleY());
		//print(snake, apple);
		clock_t end = clock();
		Sleep(TICK - (end - start));//其实运行时间基本都在1ms，根本用不到，但是如果要的话怎么办？？
		//刷新start即可
		//Sleep(TICK);
	}
}

int main()
{
	Snake snake(XUNIT, YUNIT);
	Apple apple(XUNIT, YUNIT);
	game(snake, apple);

	Sleep(1000);
	return 0;
}