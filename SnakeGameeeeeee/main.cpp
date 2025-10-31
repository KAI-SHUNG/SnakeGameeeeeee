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

//你要写一个道具类，还是苹果类，金苹果类，加速类……？

#include <easyx.h>
#include <time.h>
#include <Windows.h>
#include "Images.h"
#include "Snake.h"
#include "Apple.h"
#include "KeyBoard.h"
#include "Music.h"

#define XUNIT 16//X共16单元格
#define YUNIT 20//Y共20单元格
#define TICK 120//帧时长120ms

KeyBoard key;
Music music;
Images image(XUNIT, YUNIT);

void game()//可复用
{
	//初始化
	Snake snake(XUNIT, YUNIT);
	Apple apple(XUNIT, YUNIT);
	music.game();
	music.musicOn();
	image.gameInit();
	apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());
	//游戏主体
	int score = 0;
	while (1)
	{
		//哪里绝对有问题，好几次蛇突然不动了 
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
		clock_t start = clock();//帧率控制
		//我真是天才
		//先定义为上一个dir，有修改就改了，没修改按原来
		//省去了再写一个读取Dir[0]的函数
		char dir = *snake.SnakeDir();
		if (key.getAndPause(dir) == 1)//wasd控制 && 暂停 && 退出
		{
			int resume = 0;
			music.gamePause();
			music.click();
			// 中间显示暂停界面，之后需要分支，resume或者exit
			do {
				Sleep(TICK);//这一句好像很关键，删了不行
				image.placePause(XUNIT / 2 - 2, YUNIT / 2 - 2.5);//显示暂停
				key.flush();//清空缓冲区，用处不明
				if (key.resume())
				{
					music.click();
					break;//继续游戏
				}//（已解决）为何只有第一次对，bugbugbug(*_*)(*_*)(*_*)(*_*)
				if (key.escape())
				{
					return;//退出
					//...
				}
			} while (1);
			music.gameResume();			
			//暂停之后tick-（ end - start ）让sleep的时间为负数，所以一直停住，刷新start即可解决
			start = clock();
		}

		snake.snakeHeadNextTick(dir);//更新蛇头坐标
		if (snake.death())//死亡判定
		{
			music.gameStop();
			music.death();
			break;
			//...
		}
		if (snake.growAndMove(apple.AppleX(), apple.AppleY()))//生长 && 是否吃到苹果
		{
			score += 3;
			music.eat();
			apple.createApple(snake.SnakeX(), snake.SnakeY(), snake.SnakeLength());//生成苹果
		}

		image.flushBegin();
		image.placeSnake(snake.SnakeX(), snake.SnakeY(), snake.SnakeDir(), snake.SnakeLength());
		image.placeApple(apple.AppleX(), apple.AppleY());
		image.placeBoard(score);
		image.flushEnd();

		key.flush();//以防万一还是清空缓冲区
		clock_t end = clock();
		Sleep(TICK - (end - start));//帧率控制
	}
}

int main()
{
	game();
		
	Sleep(1000);
	return 0;
}