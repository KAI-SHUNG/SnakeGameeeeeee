#include "Image.h"
#include "Struct.h"
#pragma comment(lib,"MSIMG32.LIB")	//实现png透明通道必需的库
Image::Image(IMAGE* img0, IMAGE* img1, IMAGE* img2, IMAGE* img3)
	:Img0(img0), Img1(img1), Img2(img2), Img3(img3)
{
}
inline void Image::putimage_alpha(double x, double y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT, (BOARD + y) * UNIT, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
void Image::display_t(int clock)//center
{
	int w = Img0->getwidth();
	int h = Img0->getheight();
	int deltaY = clock / 300 % 8;
	deltaY < 4 ? deltaY = deltaY - 2 : deltaY = 6 - deltaY;
	AlphaBlend(GetImageHDC(NULL), (MENUX * UNIT - w) / 2, UNIT + deltaY, w, h,
		GetImageHDC(Img0), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
void Image::display(int time)
{
	int h = Img0->getheight();
	int w = Img0->getwidth();
	AlphaBlend(GetImageHDC(NULL), (GAMEX * UNIT - w) / 2, BOARD * UNIT, w * (TIME_TOTAL - time) / TIME_TOTAL, h,
		GetImageHDC(Img0), 0, 0, w * (TIME_TOTAL - time) / TIME_TOTAL, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
void Image::display(int x, int y)
{
	putimage_alpha(x, y, Img0);
}
void Image::display(int x, int y, char dir)
{
	switch (dir) {
	case 'w':putimage_alpha(x, y, Img0); break;
	case 'a':putimage_alpha(x, y, Img1); break;
	case 's':putimage_alpha(x, y, Img2); break;
	case 'd':putimage_alpha(x, y, Img3); break;
	}
}