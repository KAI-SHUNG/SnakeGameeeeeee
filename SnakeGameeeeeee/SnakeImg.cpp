#include "SnakeImg.h"
#include "Tools.h"
#pragma comment(lib,"MSIMG32.LIB")	//实现png透明通道必需的库
SnakeImg::SnakeImg(IMAGE* img0, IMAGE* img1, IMAGE* img2, IMAGE* img3)
	:Img0(img0), Img1(img1), Img2(img2), Img3(img3)
{
}

void SnakeImg::display(int x, int y, char dir)
{
	switch (dir) {
	case 'w':putimage_alpha(x, y + BOARD, Img0); break;
	case 'a':putimage_alpha(x, y + BOARD, Img1); break;
	case 's':putimage_alpha(x, y + BOARD, Img2); break;
	case 'd':putimage_alpha(x, y + BOARD, Img3); break;
	}
}