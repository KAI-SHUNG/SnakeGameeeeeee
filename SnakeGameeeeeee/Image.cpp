#include "Image.h"
#include "Tools.h"
#pragma comment(lib,"MSIMG32.LIB")	//实现png透明通道必需的库
Image::Image(IMAGE* img0, IMAGE* img1, IMAGE* img2, IMAGE* img3)
	:Img0(img0), Img1(img1), Img2(img2), Img3(img3)
{
}

//inline void Image::putimage_alpha(double x, double y, IMAGE* img)
//{
//	int w = img->getwidth();
//	int h = img->getheight();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT,  y * UNIT, w, h,
//		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
//}

void Image::display(int time)
{
	int w = Img0->getwidth();
	int h = Img0->getheight();
	AlphaBlend(GetImageHDC(NULL), (GAMEX * UNIT - w) / 2, BOARD * UNIT, w * (TIME_TOTAL - time) / TIME_TOTAL, h,
		GetImageHDC(Img0), 0, 0, w * (TIME_TOTAL - time) / TIME_TOTAL, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
void Image::display_t(int clock)
{
	double deltaY = clock / 300 % 10;//?
	deltaY < 5 ? deltaY = deltaY - 2.5 : deltaY = 7.5 - deltaY;
	putimage_alpha_c(MENUX / 2, 6 + deltaY / UNIT, Img0);
}
//void Image::display(double x, double y)
//{
//	putimage_alpha(x, y, Img0);
//}
//void Image::display_c(double x, double y)
//{
//	int w = Img0->getwidth();
//	int h = Img0->getheight();
//	putimage_alpha(x - w / 2.0 / UNIT, y - h / 2.0 / UNIT, Img0);
//}
void Image::display(int x, int y, char dir)
{
	switch (dir) {
	case 'w':putimage_alpha(x, y + BOARD, Img0); break;
	case 'a':putimage_alpha(x, y + BOARD, Img1); break;
	case 's':putimage_alpha(x, y + BOARD, Img2); break;
	case 'd':putimage_alpha(x, y + BOARD, Img3); break;
	}
}