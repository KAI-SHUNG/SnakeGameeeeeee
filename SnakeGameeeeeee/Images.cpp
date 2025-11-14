#include "Images.h"
#include <easyx.h>
#include <vector>
#include <iostream>
#pragma comment(lib,"MSIMG32.LIB")	//实现png透明通道必需的库

#define BKCOLOR 0xF0FFF0			//背景颜色
#define BOARDCOLOR 0x66B2FF			//计分板颜色
#define LINECOLOR 0x0066CC			//计分板边框颜色
#define TEXTCOLOR 0x003366			//字体颜色
#define UNIT 10						//UNIT_SIZE每个单元格10x10像素
#define BOARD 2						//计分板行格数
#define RATIO 2.5					//放大比例

IMAGE sHeadW, sHeadA, sHeadS, sHeadD;//蛇头
IMAGE sBodyAD, sBodyWS;//蛇身
IMAGE sTurnUL, sTurnDR, sTurnDL, sTurnUR;//蛇转弯
IMAGE sTailW, sTailA, sTailS, sTailD;//蛇尾
IMAGE apple, goldApple;
IMAGE wall;
IMAGE title;
IMAGE pause;
IMAGE bar;
LOGFONT textFont_;
LOGFONT numberFont;
IMAGE tempImage;

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int h = img->getheight();
	int w = img->getwidth();
	AlphaBlend(GetImageHDC(NULL), x * UNIT, (BOARD + y) * UNIT, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void setTextFont()
{
	textFont_.lfHeight = 24;
	textFont_.lfWeight = FW_BOLD;
	textFont_.lfItalic = 0;
	textFont_.lfQuality = PROOF_QUALITY;
	_tcscpy_s(textFont_.lfFaceName, _T("Courier New"));
	setbkmode(TRANSPARENT);
	settextcolor(TEXTCOLOR);
}
void setNumberFont()
{
	numberFont.lfHeight = 25;
	numberFont.lfWeight = FW_BOLD;
	numberFont.lfItalic = 0;
	numberFont.lfQuality = PROOF_QUALITY;
	_tcscpy_s(numberFont.lfFaceName, _T("ROG Fonts"));
	setbkmode(TRANSPARENT);
	settextcolor(TEXTCOLOR);
	settextstyle(&numberFont);
}

//输入地图单元格数x，y
Images::Images(int menux, int menuy, int unitx, int unity)
	:MenuX(menux), MenuY(menuy),UnitX(unitx), UnitY(unity)
{
}
int Images::loadImages()
{
	if (loadimage(&apple, _T("./Resource/Images/apple.png"))
		+ loadimage(&goldApple, _T("./Resource/Images/gold_apple.png"))
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
		+ loadimage(&sTailD, _T("./Resource/Images/snake_tail_d.png"))
		+ loadimage(&wall, _T("./Resource/Images/wall.png"))
		+ loadimage(&title, _T("./Resource/Images/title.png"))
		+ loadimage(&pause, _T("./Resource/Images/pause.png"))
		+ loadimage(&bar, _T("./Resource/Images/bar.png"))
		!= 0)
	{
		std::cerr << "Image Resource ERROR!\n";
		return 1;
	}
	else 
	{
		return 0;
	}
}
void Images::menuInit()
{
	initgraph(MenuX * UNIT * RATIO, MenuY * UNIT * RATIO);
	setaspectratio(RATIO, RATIO);//10x10->25*25
	setbkcolor(BKCOLOR);
	cleardevice();
}
void Images::gameInit()
{
	initgraph(UnitX * UNIT * RATIO, (BOARD + UnitY) * UNIT * RATIO, EX_NOCLOSE);
	setaspectratio(RATIO, RATIO);//10x10->25*25
	setbkcolor(BKCOLOR);
	cleardevice();
	//计分板样式
	setfillcolor(BOARDCOLOR);
	setlinecolor(LINECOLOR);
	setlinestyle(PS_DASH);
	//字体样式
	gettextstyle(&textFont_);
	gettextstyle(&numberFont);
	setTextFont();
	setNumberFont();
}

void Images::placeSnake(const int* snakeX, const int* snakeY, const char* snakeDir, int snakeLength)
{
	snakeHead(snakeX[0], snakeY[0], snakeDir[0]);
	for (int i = 1; i < snakeLength - 1; ++i)
	{
		snakeBody(snakeX[i], snakeY[i],
			snakeDir[i], snakeDir[i - 1]);
		//注意这里反直觉，方向靠近蛇头的为下一个，但是是i - 1
	}
	snakeTail(snakeX[snakeLength - 1],
		snakeY[snakeLength - 1],
		snakeDir[snakeLength - 2]);
	//注意这里snakeTial读取的应该是length-2的Dir
}
void Images::placeApple(int x, int y)
{
	putimage_alpha(x, y, &apple);
}
void Images::placeGoldApple(int x, int y)
{
	putimage_alpha(x, y, &goldApple);
}

//void Images::placeButton(int x, int y, bool state)
//{
//	int h = button.getheight();
//	int w = button.getwidth();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, (BOARD + y) * UNIT - h / 2, w, h,
//		GetImageHDC(state ? &buttonPressed : &button), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
//}
//void Images::placePlay(int x, int y, bool state)
//{
//	int h = buttonPlay.getheight();
//	int w = buttonPlay.getwidth();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT - h / 2, w, h,
//		GetImageHDC(state ? &buttonPlayPressed : &buttonPlay), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
//}
//void Images::placeAgain(int x, int y, bool state)
//{
//	int h = buttonAgain.getheight();
//	int w = buttonAgain.getwidth();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT - h / 2, w, h,
//		GetImageHDC(state ? &buttonAgainPressed : &buttonAgain), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
//}
//void Images::placeExit(int x, int y, bool state)
//{
//	int h = buttonExit.getheight();
//	int w = buttonExit.getwidth();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT - h / 2, w, h,
//		GetImageHDC(state ? &buttonExitPressed : &buttonExit), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
//}
//void Images::placeButtonPressed(int x, int y)
//{
//	putimage_alpha(x, y, &buttonPressed);
//}
void Images::placeWall(int x, int y)
{
	putimage_alpha(x, y, &wall);
}
void Images::placeTitle(int clock)
{
	int deltaY = clock / 300 % 8 ;
	deltaY < 4 ? deltaY = deltaY - 2 : deltaY = 6 - deltaY;
	int h = title.getheight();
	int w = title.getwidth();
	AlphaBlend(GetImageHDC(NULL), (MenuX * UNIT - w) / 2, UNIT + deltaY, w, h,
		GetImageHDC(&title), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
void Images::placePause(int x, int y)
{
	putimage_alpha(x, y, &pause);
}
void Images::placeBoard(int score)
{
	fillrectangle(0, 0, UnitX * UNIT, BOARD * UNIT);

	TCHAR textScore[] = _T("Score:");
	settextstyle(&textFont_);
	outtextxy(0, 0, textScore);

	TCHAR Score[6];
	_stprintf_s(Score, _T("%d"), score);
	settextstyle(&numberFont);
	outtextxy(7.5 * UNIT, -3, Score);
}
void Images::placeBar(int time, int time_total)
{
	int h = bar.getheight();
	int w = bar.getwidth();
	AlphaBlend(GetImageHDC(NULL), (UnitX * UNIT - w) / 2, BOARD * UNIT, w * (time_total - time) / time_total, h,
		GetImageHDC(&bar), 0, 0, w * (time_total - time) / time_total, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void Images::flushBegin()
{
	BeginBatchDraw();
	cleardevice();
}
void Images::flushEnd()
{
	EndBatchDraw();
}
void Images::temp()
{
	getimage(&tempImage, 0, 0, UnitX * UNIT, (BOARD + UnitY) * UNIT);
}
void Images::tempDisplay()
{
	putimage(0, 0, &tempImage);
}

void Images::snakeHead(int x, int y, char dir)
{
	switch (dir) {
	case 'w':putimage_alpha(x, y, &sHeadW); break;
	case 'a':putimage_alpha(x, y, &sHeadA); break;
	case 's':putimage_alpha(x, y, &sHeadS); break;
	case 'd':putimage_alpha(x, y, &sHeadD); break;
	}
}
//snakebody&snaketurn大一统!!
void Images::snakeBody(int x, int y, char dir0, char dir1)
{
	switch (dir0)
	{
	case 'w':
		switch (dir1)
		{
		case('a'):putimage_alpha(x, y, &sTurnDL); break;
		case('w'):putimage_alpha(x, y, &sBodyWS); break;
		case('d'):putimage_alpha(x, y, &sTurnDR); break;
		}break;

	case 'a':
		switch (dir1)
		{
		case('w'):putimage_alpha(x, y, &sTurnUR); break;
		case('a'):putimage_alpha(x, y, &sBodyAD); break;
		case('s'):putimage_alpha(x, y, &sTurnDR); break;
		}break;

	case 's':
		switch (dir1)
		{
		case('a'):putimage_alpha(x, y, &sTurnUL); break;
		case('s'):putimage_alpha(x, y, &sBodyWS); break;
		case('d'):putimage_alpha(x, y, &sTurnUR); break;
		}break;

	case 'd':
		switch (dir1)
		{
		case('w'):putimage_alpha(x, y, &sTurnUL); break;
		case('s'):putimage_alpha(x, y, &sTurnDL); break;
		case('d'):putimage_alpha(x, y, &sBodyAD); break;
		}break;
	}
}
void Images::snakeTail(int x, int y, char dir)
{
	switch (dir) {
	case 'w':putimage_alpha(x, y, &sTailW); break;
	case 'a':putimage_alpha(x, y, &sTailA); break;
	case 's':putimage_alpha(x, y, &sTailS); break;
	case 'd':putimage_alpha(x, y, &sTailD); break;
	}
}
//void Images::test()
//{
//	placeApple(1, 0);
//	placeGoldApple(1, 1);
//	snakeHead(0, 0, 'w');
//	snakeHead(0, 1, 'a');
//	snakeHead(0, 2, 's');
//	snakeHead(0, 3, 'd');
//	snakeBody(0, 4, 'w', 'w');
//	snakeBody(0, 5, 'a', 'a');
//	snakeBody(1, 5, 's', 's');
//	snakeBody(1, 4, 'd', 'd');
//	snakeBody(1, 7, 'w', 'd'); snakeBody(1, 7, 'a', 's');//测试正确性
//	snakeBody(2, 7, 'd', 's'); snakeBody(2, 7, 'w', 'a');//测试正确性
//	snakeBody(1, 8, 'a', 'w'); snakeBody(1, 8, 's', 'd');//测试正确性
//	snakeBody(2, 8, 's', 'a'); snakeBody(2, 8, 'd', 'w');//测试正确性
//	snakeBody(1, 9, ' w', 'w');
//	snakeTail(0, 6, 'w');
//	snakeTail(0, 7, 'a');
//	snakeTail(0, 8, 's');
//	snakeTail(0, 9, 'd');
//	placeButton(0, 10);
//	placeButtonPressed(0, 11);
//	placeSoundOn(0, 12);
//	placeSoundOff(0, 14);
//	placeWall(0, 16);
//	placeTitle(0);
//	placePause(6, 6);
//}