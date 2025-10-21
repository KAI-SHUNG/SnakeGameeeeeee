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

//下一步				计分板
//下下一步			menu界面，鼠标控制的加入，再来一局的重置
//下下下一步			金苹果的加入
//下下下下一步		排行榜、存档
//下下下下下一步		声音控制功能
//下下下下下下一步	不同地图
#include <easyx.h>
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

KeyBoard key;
Music music;
Images image(XUNIT, YUNIT);

void game(Snake& snake, Apple& apple)
{
	//初始化
	music.game();
	music.musicOn();
	image.init();

	apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());
	while (1)
	{
		//哪里绝对有问题，好几次蛇突然不动了
		clock_t start = clock();
		
		//我真是天才
		//先定义为上一个dir，有修改就改了，没修改按原来
		//省去了再写一个读取Dir[0]的函数
		char dir = *snake.SnakeDir();
		if (key.getAndPause(dir) == 1)
		{
			int resume = 0;				
			music.gamePause();
			music.click();
			do {
				Sleep(TICK);
				key.flush();
				if (key.resume())
				{
					music.click();
					break;
				}
				//为何只有第一次对，bugbugbug(*_*)(*_*)(*_*)(*_*)
				//应该是缓冲区的问题
				if (key.escape())
				{
					return;
				}
			} while (1);
			music.gameResume();
			// 中间显示暂停界面，之后需要分支，resume或者exit
			//之后tick-（end-start）让sleep的时间为负数，所以一直停住
			start = clock();//刷新start即可解决
			//pause
		}
		snake.snakeHeadNextTick(dir);
		if (snake.death())
		{
			music.gameStop();
			music.death();
			break;
		}
		//哪里绝对有问题，好几次蛇突然不动了
		if (snake.growAndMove(apple.AppleX(), apple.AppleY()))
		{
			//生成苹果
			music.eat();
			apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());
		}
		image.stage(snake.SnakeX(), snake.SnakeY(), snake.SnakeDir(), snake.SnakeLength(),
			apple.AppleX(), apple.AppleY());
		key.flush();
		clock_t end = clock();
		Sleep(TICK - (end - start));
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