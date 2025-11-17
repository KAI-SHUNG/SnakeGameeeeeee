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
//4.生成道具，护盾
//5.地图，有不同wall
//7.计时器，指定时间后道具/果实消失 ^^^
//8.图形界面，排行榜

//分离,解耦合!!
//如果未来客户要换一个图形库,你的代码怎么复用??
//game游戏逻辑和images图形分离
//你要写一个道具类 ^^^，还是苹果类，金苹果类，加速类……？

//下一步				计分板 ^^^
//下下下一步			金苹果的加入：^^^
//						吃六个苹果生成金苹果 ^^^ ，在sweet moment吃到金苹果下一次变为吃三个苹果就生成金苹果 ^^^
//							仿照高中诺基亚的逻辑，倒计时6秒，加分递减，sweet moment: 5 ^^^
//							加一个进度条，可以倒计时 ^^^
//下下一步			menu界面 ^^^ ，再来一局的重置 ^^^ ， 鼠标控制的加入 ^^^，难度选择 
//下下下下一步		menu排行榜、存档
//下下下下下一步		声音控制功能
//下下下下下下一步	不同地图

/*
	2025/11/13 修复了调试后无法移动的bug 
	不知道哪里有问题，好几次蛇突然不动了 
	莫名其妙的bug(*_*)(*_*)(*_*)(*_*)(*_*)(*_*)
	给你👻辣，给你上香
	好像好久没出现了？ 2025/11/7
	知道为什么解决了，因为调试时sleeptime是负数 2025/11/13
*/

/*-------------------------------------------------------------------------------------------------
				***								***								***
				|||								|||								|||
				|||								|||								|||
				|||								|||								|||
			———————————						———————————						———————————
			\		  /						\		  /						\		  /
			 \_______/						 \_______/						 \_______/
-------------------------------------------------------------------------------------------------*/

#include <easyx.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Button.h"
#include "Item.h"
#include "Image.h"
#include "Images.h"
#include "Keyboard.h"
#include "Music.h"
#include "Timer.h"
#include "Snake.h"
#include "Struct.h"

IMAGE titleImg, button, buttonPressed;
IMAGE soundOn, soundOff;
IMAGE appleImg, goldappleImg;
IMAGE pauseImg, barImg, wallImg, tempImg;
IMAGE sHeadW, sHeadA, sHeadS, sHeadD;//蛇头
IMAGE sBodyAD, sBodyWS;//蛇身
IMAGE sTurnUL, sTurnDR, sTurnDL, sTurnUR;//蛇转弯
IMAGE sTailW, sTailA, sTailS, sTailD;//蛇尾

Image title(&titleImg), pause(&pauseImg), bar(&barImg), wall(&wallImg);
//蛇头蛇身蛇弯蛇尾全部大一统！！！ 2025/11/17
Image head(&sHeadW, &sHeadA, &sHeadS, &sHeadD);
Image bodyW(&sBodyWS, &sTurnDL, nullptr, &sTurnDR);
Image bodyA(&sTurnUR, &sBodyAD, &sTurnDR, nullptr);
Image bodyS(nullptr, &sTurnUL, &sBodyWS, &sTurnUR);
Image bodyD(&sTurnUL, nullptr, &sTurnDL, &sBodyAD);
Image tail(&sTailW, &sTailA, &sTailS, &sTailD);
int loadImage();
int loadFont();
int resourceCheck();


void Menu();
//#define UNIT 10				//UNIT_SIZE每个单元格10x10像素
//#define MENUX 24			//菜单界面X共24单元格
//#define MENUY 20			//菜单界面Y共20单元格


void Mode();
void Sound();

int Game();
//#define UNITX 16			//游戏界面X共16单元格
//#define UNITY 20			//游戏界面Y共20单元格
//#define BOARD 2				//计分板宽度
#define TICK_EASY 250		//简单模式帧时长250ms
#define TICK_NORMAL 160		//普通模式帧时长160ms
#define TICK_HARD 100		//困难模式帧时长100ms
#define TICK_HELL 85		//地狱模式帧时长85ms
#define POINT_APPLE 1		//苹果分值
#define POINT_GOLDAPPLE 26	//金苹果分值
void snakedisplay(std::vector<Coordinate>);


void Gameover();


Images image(MENUX, MENUY, UNITX, UNITY);
Keyboard keyboard;
Music music;
SceneState scene_state = SceneState::MENU;
int main()
{
	if (resourceCheck())
	{
		std::cerr << "资源文件错误！ERROR_RESOURECES!\n";
		system("pause");
		return 1;
	}
	while (true)
	{
		int score = 0;//未来排行榜
		switch (scene_state)
		{
		case(SceneState::MENU):
			Menu(); 
			break;
		case(SceneState::MODE):
			break;
		case(SceneState::GAME):
			score = Game();
			break;
		case(SceneState::GAMEOVER):
			Gameover();
			break;
		case(SceneState::EXIT):
			return 0;
		}
		Sleep(TICK_NORMAL);//很关键，留下缓冲时间
	}
}


int loadImage()
{
	if (0
		+ loadimage(&titleImg, _T("./Resource/Images/title.png"))
		+ loadimage(&button, _T("./Resource/Images/button.png"))
		+ loadimage(&buttonPressed, _T("./Resource/Images/button_pressed.png"))
		+ loadimage(&soundOn, _T("./Resource/Images/sound_on.png"))
		+ loadimage(&soundOff, _T("./Resource/Images/sound_off.png"))
		+ loadimage(&appleImg, _T("./Resource/Images/apple.png"))
		+ loadimage(&goldappleImg, _T("./Resource/Images/goldapple.png"))
		+ loadimage(&pauseImg, _T("./Resource/Images/pause.png"))
		+ loadimage(&barImg, _T("./Resource/Images/bar.png"))
		+ loadimage(&wallImg, _T("./Resource/Images/wall.png"))
		+ loadimage(&sHeadW, _T("./Resource/Images/snake_head_w.png"))
		+ loadimage(&sHeadA, _T("./Resource/Images/snake_head_a.png"))
		+ loadimage(&sHeadS, _T("./Resource/Images/snake_head_s.png"))
		+ loadimage(&sHeadD, _T("./Resource/Images/snake_head_d.png"))
		+ loadimage(&sBodyAD, _T("./Resource/Images/snake_body_ad.png"))
		+ loadimage(&sBodyWS, _T("./Resource/Images/snake_body_ws.png"))
		+ loadimage(&sTurnUL, _T("./Resource/Images/snake_turn_ul.png"))
		+ loadimage(&sTurnDR, _T("./Resource/Images/snake_turn_dr.png"))
		+ loadimage(&sTurnDL, _T("./Resource/Images/snake_turn_dl.png"))
		+ loadimage(&sTurnUR, _T("./Resource/Images/snake_turn_ur.png"))
		+ loadimage(&sTailW, _T("./Resource/Images/snake_tail_w.png"))
		+ loadimage(&sTailA, _T("./Resource/Images/snake_tail_a.png"))
		+ loadimage(&sTailS, _T("./Resource/Images/snake_tail_s.png"))
		+ loadimage(&sTailD, _T("./Resource/Images/snake_tail_d.png")) == 0)
	{
		return 0;
	}
	else
	{
		std::cerr << "Image Resources ERROR!\n";
		return 1;
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
int resourceCheck()
{
	return loadImage() + image.loadImages() + loadFont() + music.loadMusic();
}


void Menu()
{
	MenuState menu_state = MenuState::PLAY;

	image.menuInit();
	music.menu();
	Timer timer;

	TCHAR text_play[] = "PLAY";
	Button btn_menu_play(&button, &buttonPressed, MENUX / 2, 12);
	TCHAR text_exit[] = "EXIT";
	Button btn_menu_exit(&button, &buttonPressed, MENUX / 2, 15);
	Image title(&titleImg);
	while (true)
	{
		BeginBatchDraw();
		cleardevice();
		//Get Mouse event
		ExMessage msg;
		peekmessage(&msg);
		//Mouse event
		btn_menu_play.check(&msg);
		btn_menu_exit.check(&msg);
		if (btn_menu_play.isPressed){menu_state = MenuState::PLAY;}
		if (btn_menu_exit.isPressed){menu_state = MenuState::EXIT;}
		//Keyboard event
		if (menu_state == MenuState::EXIT && keyboard.escape()) { btn_menu_exit.isClicked = true; };
		keyboard.menu(menu_state);
		if (keyboard.enter()) {
			switch (menu_state) {
			case(MenuState::PLAY):btn_menu_play.isClicked = true; break;
			case(MenuState::EXIT):btn_menu_exit.isClicked = true; break;
			}
		}
		//Clicked
		if (btn_menu_play.isClicked){scene_state = SceneState::GAME;return;}
		if (btn_menu_exit.isClicked){scene_state = SceneState::EXIT;return;}
		switch (menu_state) {
		case(MenuState::PLAY):btn_menu_play.isPressed = true; btn_menu_play.isOn= true; break;
		case(MenuState::EXIT):btn_menu_exit.isPressed = true; btn_menu_exit.isOn= true; break;
		}//如果没有上述switch语句，按键只受鼠标位置影响，等于可以砍掉键盘，纯鼠标
		//Image
		btn_menu_play.display(text_play);
		btn_menu_exit.display(text_exit);
		title.display_t(timer.getTime());
		EndBatchDraw();
		flushmessage();
		Sleep(TICK_NORMAL);
	}
}


void Mode()
{

}


void Sound()
{
	Button btn_sound_music(&soundOn, &soundOff, MENUX / 2, 11);
	Button btn_sound_effect(&soundOn, &soundOff, MENUX / 2, 11);
}


int Game()
{
	//Initialize
	image.gameInit();
	Item apple		(UNITX, UNITY, &appleImg);
	Item goldapple	(UNITX, UNITY, &goldappleImg);
	music.menuStop();
	music.game();
	Snake snake(UNITX, UNITY);
	Timer timer;

	int score = 0;
	int tick = TICK_HARD;//未来难度选择
	while (true)
	{
		//Frametime Control
		timer.frameStart();
		// Pause && Exit
		if (keyboard.space() || keyboard.escape())
		{
			pause.display(UNITX / 2 - 2, UNITY / 2 - 3);
			music.click();
			Sleep(TICK_EASY);
			music.gamePause();
			while (true)
			{
				Sleep(TICK_EASY);
				if (keyboard.space())
				{
					music.click();
					Sleep(TICK_EASY);
					flushmessage();
					break;//Resume Game
				}
				if (keyboard.escape())
				{
					music.gameStop();
					scene_state = SceneState::MENU;
					return -1;//Back to Menu, NO Score
				}
			}
			music.gameResume();
			timer.frameStart();
		}
		//Snake Movement Control
		/*我真是天才
		先定义为上一个dir，有修改就改了，没修改按原来
		省去了再写一个读取Dir[0]的函数*/
		char dir = snake.coord().at(0).Dir;
		keyboard.move(dir);
		//Update SnakeHead Coordinate
		snake.snakeHeadNextTick(dir);
		//Death Check
		if (snake.death())
		{
			getimage(&tempImg, 0, 0, UNITX * UNIT, (BOARD + UNITY) * UNIT);
			music.death();
			music.gameStop();
			scene_state = SceneState::GAMEOVER;
			return score;
		}
		//Goldapple Timeout Check
		int goldAppleTime = timer.goldAppleTime();
		if (goldAppleTime > TIME_TOTAL)
		{
			goldapple.exist = false;
		}
		//Check If Eat Apple and Goldapple && Snake Grow
		if (snake.eatApple(apple.get_x(), apple.get_y()))
		{
			music.eat();
			score += POINT_APPLE;
			apple.counter += 1;
			apple.reset();
		}
		else if (goldapple.exist && snake.eatGoldApple(goldapple.get_x(), goldapple.get_y()))
		{
			music.bell();
			music.eat();
			score += POINT_GOLDAPPLE * (TIME_TOTAL - goldAppleTime) / TIME_TOTAL;
			if (goldAppleTime / 1000 == 1)
			{
				music.bell();
				apple.counter += 3;
			}
			goldapple.reset();
		}
		//Snake Move
		snake.move();
		//Create Apple and Goldapple
		if (!apple.exist)
		{
			apple.create(snake.coord(), goldapple.get_x(), goldapple.get_y());
			apple.exist = true;
			if (apple.counter % 6 == 0 && !goldapple.exist && apple.counter != 0)
			{
				goldapple.create(snake.coord(), apple.get_x(), apple.get_y());
				goldapple.exist = true;
				timer.goldAppleCreate();
			}
		}
		//Image
		BeginBatchDraw();
		cleardevice(); 
		if (goldapple.exist)
		{
			bar.display(timer.goldAppleTime());
			goldapple.display();
		}
		apple.display();
		image.placeBoard(score);
		snakedisplay(snake.coord());
		EndBatchDraw();
		flushmessage();
		//Frametime Control
		if (tick - timer.frameTime() > 0)
			Sleep(tick - timer.frameTime());
	}
}
void Gameover()
{
	GameoverState over_state = GameoverState::AGAIN;

	TCHAR text_again[] = "AGAIN";
	Button btn_over_again(&button, &buttonPressed, UNITX / 2, 10);
	TCHAR text_back[] = "BACK";
	Button btn_over_back(&button, &buttonPressed, UNITX / 2, 13);

	while (true)
	{
		BeginBatchDraw();
		cleardevice();
		//Get Mouse event
		ExMessage msg;
		peekmessage(&msg);
		//Mouse event
		btn_over_again.check(&msg);
		btn_over_back.check(&msg);
		if (btn_over_again.isPressed) { over_state = GameoverState::AGAIN; }
		if (btn_over_back.isPressed) { over_state = GameoverState::BACK; }
		//Keyboard event
		if (over_state == GameoverState::BACK && keyboard.escape()) { btn_over_back.isClicked = true; };
		keyboard.gameover(over_state);
		if (keyboard.enter()) {
			switch (over_state) {
			case(GameoverState::AGAIN):btn_over_again.isClicked = true; break;
			case(GameoverState::BACK):btn_over_back.isClicked = true; break;
			}
		}
		//Clicked
		if (btn_over_again.isClicked) { scene_state = SceneState::GAME; return; }
		if (btn_over_back.isClicked) { scene_state = SceneState::MENU; return; }
		switch (over_state) {
		case(GameoverState::AGAIN):btn_over_again.isPressed = true; btn_over_again.isOn = true; break;
		case(GameoverState::BACK):btn_over_back.isPressed = true; btn_over_back.isOn = true; break;
		}
		//Image
		putimage(0, 0, &tempImg);
		btn_over_again.display(text_again);
		btn_over_back.display(text_back);
		EndBatchDraw();
		flushmessage();
		Sleep(TICK_NORMAL);
	}
}


void snakedisplay(std::vector<Coordinate> coord)
{
	head.display(coord.begin()->X, coord.begin()->Y, coord.begin()->Dir);
	for (auto it = coord.begin(); it != coord.end() - 1; ++it)
	{
		switch (it->Dir)
		{
		case('w'):bodyW.display(it->X, it->Y, (it - 1)->Dir); break;
		case('a'):bodyA.display(it->X, it->Y, (it - 1)->Dir); break;
		case('s'):bodyS.display(it->X, it->Y, (it - 1)->Dir); break;
		case('d'):bodyD.display(it->X, it->Y, (it - 1)->Dir); break;
		}
	}
	tail.display((coord.end() - 1)->X, (coord.end() - 1)->Y, (coord.end() - 2)->Dir);
}