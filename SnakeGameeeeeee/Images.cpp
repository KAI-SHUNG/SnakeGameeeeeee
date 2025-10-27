#include "Images.h"
#include <easyx.h>
#pragma comment(lib,"MSIMG32.LIB")	//实现png透明通道必需的库

#define BKCOLOR 0xF0FFF0			//背景颜色
#define BOARDCOLOR 0x66B2FF			//计分板颜色
#define LINECOLOR 0x0066CC			//计分板边框颜色
#define TEXTCOLOR 0x003366			//字体颜色
#define UNIT 10						//UNIT_SIZE每个单元格10x10像素
#define BOARD 8						//计分板单元格数
#define RATIO 2.5					//放大比例

IMAGE apple;
IMAGE goldApple;
IMAGE sHeadW;
IMAGE sHeadA;
IMAGE sHeadS;
IMAGE sHeadD;
IMAGE sBodyAD;
IMAGE sBodyWS;
IMAGE sTurnUL;
IMAGE sTurnDR;
IMAGE sTurnDL;
IMAGE sTurnUR;
IMAGE sTailW;
IMAGE sTailA;
IMAGE sTailS;
IMAGE sTailD;
IMAGE button;
IMAGE buttonPressed;
IMAGE soundOn;
IMAGE soundOff;
IMAGE wall;
IMAGE title;
IMAGE pause;

//输入地图单元格数x，y
Images::Images(int unitx, int unity)
	:UnitX(unitx), UnitY(unity)
{

	loadimage(&apple, _T("./Resource/Images/apple.png"));
	loadimage(&goldApple, _T("./Resource/Images/gold_apple.png"));
	loadimage(&sHeadW, _T("./Resource/Images/snake_head_w.png"));
	loadimage(&sHeadA, _T("./Resource/Images/snake_head_a.png"));
	loadimage(&sHeadS, _T("./Resource/Images/snake_head_s.png"));
	loadimage(&sHeadD, _T("./Resource/Images/snake_head_d.png"));
	loadimage(&sBodyAD, _T("./Resource/Images/snake_body_ad.png"));
	loadimage(&sBodyWS, _T("./Resource/Images/snake_body_ws.png"));
	loadimage(&sTurnUL, _T("./Resource/Images/snake_turn_ul.png"));
	loadimage(&sTurnDR, _T("./Resource/Images/snake_turn_dr.png"));
	loadimage(&sTurnDL, _T("./Resource/Images/snake_turn_dl.png"));
	loadimage(&sTurnUR, _T("./Resource/Images/snake_turn_ur.png"));
	loadimage(&sTailW, _T("./Resource/Images/snake_tail_w.png"));
	loadimage(&sTailA, _T("./Resource/Images/snake_tail_a.png"));
	loadimage(&sTailS, _T("./Resource/Images/snake_tail_s.png"));
	loadimage(&sTailD, _T("./Resource/Images/snake_tail_d.png"));
	loadimage(&button, _T("./Resource/Images/button.png"));
	loadimage(&buttonPressed, _T("./Resource/Images/button_pressed.png"));
	loadimage(&soundOn, _T("./Resource/Images/sound_on.png"));
	loadimage(&soundOff, _T("./Resource/Images/sound_off.png"));
	loadimage(&wall, _T("./Resource/Images/wall.png"));
	loadimage(&title, _T("./Resource/Images/title.png"));
	loadimage(&pause, _T("./Resource/Images/pause.png"));
}

//考虑到视觉美观，定义了double重载
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int h = img->getheight();
	int w = img->getwidth();
	AlphaBlend(GetImageHDC(NULL), x * UNIT, y * UNIT, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void putimage_alpha(double x, double y, IMAGE* img)
{
	int h = img->getheight();
	int w = img->getwidth();
	AlphaBlend(GetImageHDC(NULL), x * UNIT, y * UNIT, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void Images::gameInit()
{
	initgraph((BOARD + UnitX) * UNIT * RATIO, UnitY * UNIT * RATIO);
	setaspectratio(RATIO, RATIO);//10x10->25*25
	setbkcolor(BKCOLOR);
	cleardevice();
	//计分板样式
	setfillcolor(BOARDCOLOR);
	setlinecolor(LINECOLOR);
	setlinestyle(PS_DASH);
	//字体样式
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	f.lfWeight = FW_BOLD;
	f.lfItalic = 1;
	_tcscpy_s(f.lfFaceName, _T("Centuries"));
	f.lfQuality = PROOF_QUALITY;
	setbkmode(TRANSPARENT);
	settextcolor(TEXTCOLOR);
	settextstyle(&f);
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

void Images::placeApple(int x, int y)
{
	putimage_alpha(x, y, &apple);
}

void Images::placeGoldApple(int x, int y)
{
	putimage_alpha(x, y, &goldApple);
}

void Images::placeButton(int x, int y)
{
	putimage_alpha(x, y, &button);
}

void Images::placeButtonPressed(int x, int y)
{
	putimage_alpha(x, y, &buttonPressed);
}

void Images::placeSoundOn(int x, int y)
{
	putimage_alpha(x, y, &soundOn);
}

void Images::placeSoundOff(int x, int y)
{
	putimage_alpha(x, y, &soundOff);
}

void Images::placeWall(int x, int y)
{
	putimage_alpha(x, y, &wall);
}

void Images::placeTitle(int x, int y)
{
	putimage_alpha(x, y, &title);
}

void Images::placePause(double x, double y)
{
	putimage_alpha(x, y, &pause);
}

void Images::placeBoard()
{
	TCHAR text1[] = _T("Score:");
	outtextxy(UnitX * UNIT + 5, 5, text1);
}

void Images::flushBegin()
{
	BeginBatchDraw();
	cleardevice();
	fillrectangle(UnitX * UNIT, 0, (BOARD + UnitX) * UNIT, UnitY * UNIT);
}

void Images::flushEnd()
{
	EndBatchDraw();
}

void Images::test()
{
	placeApple(1, 0);
	placeGoldApple(1, 1);
	snakeHead(0, 0, 'w');
	snakeHead(0, 1, 'a');
	snakeHead(0, 2, 's');
	snakeHead(0, 3, 'd');
	snakeBody(0, 4, 'w', 'w');
	snakeBody(0, 5, 'a', 'a');
	snakeBody(1, 5, 's', 's');
	snakeBody(1, 4, 'd', 'd');
	snakeBody(1, 7, 'w', 'd'); snakeBody(1, 7, 'a', 's');//测试正确性
	snakeBody(2, 7, 'd', 's'); snakeBody(2, 7, 'w', 'a');//测试正确性
	snakeBody(1, 8, 'a', 'w'); snakeBody(1, 8, 's', 'd');//测试正确性
	snakeBody(2, 8, 's', 'a'); snakeBody(2, 8, 'd', 'w');//测试正确性
	snakeBody(1, 9, ' w', 'w');
	snakeTail(0, 6, 'w');
	snakeTail(0, 7, 'a');
	snakeTail(0, 8, 's');
	snakeTail(0, 9, 'd');
	placeButton(0, 10);
	placeButtonPressed(0, 11);
	placeSoundOn(0, 12);
	placeSoundOff(0, 14);
	placeWall(0, 16);
	placeTitle(1, 0);
	placePause(6, 6);
}
