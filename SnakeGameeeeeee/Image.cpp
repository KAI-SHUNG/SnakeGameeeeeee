#include "Image.h"
#define UNIT 10
Image::Image()
{

}
Image::Image(IMAGE* img):Img(img)
{
}
void Image::display(int x, int y)
{
	int h = Img->getheight();
	int w = Img->getwidth();
	AlphaBlend(GetImageHDC(NULL), x * UNIT, y * UNIT, w, h,
		GetImageHDC(Img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
//void Image::display(int x, int y, bool state)
//{
//	int h = Img0->getheight();
//	int w = Img0->getwidth();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT, y * UNIT, w, h,
//		GetImageHDC(state ? Img1 : Img0), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
//}
//void Image::display(int x, int y, int time, int time_total)
//{
//	int h = Img0->getheight();
//	int w = Img0->getwidth();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT, w * (time_total - time) / time_total, h,
//		GetImageHDC(Img0), 0, 0, w * (time_total - time) / time_total, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
//}