#include "Button.h"
#define UNIT 10

Button::Button(IMAGE* img, IMAGE* img_pressed, int x_in, int y_in)
	:Img(img), Img_pressed(img_pressed),x(x_in),y(y_in)
{
	gettextstyle(&textFont);
}
void Button::display(bool is_pressed)
{
	int w = Img->getwidth();
	int h = Img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT, w, h,
		GetImageHDC(is_pressed ? Img_pressed : Img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
//void Button::display(bool is_pressed,TCHAR text[])
//{
//	int w = Img->getwidth();
//	int h = Img->getheight();
//	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT, w, h,
//		GetImageHDC(is_pressed ? Img_pressed : Img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
//	setTextFont();
//	outtextxy(x, y, text);
//}
bool Button::isPressed()
{
	
}
bool Button::isClicked()
{

}
void Button::setTextFont()
{
	textFont.lfHeight = 24;
	textFont.lfWeight = FW_BOLD;
	textFont.lfItalic = 0;
	textFont.lfQuality = PROOF_QUALITY;
	_tcscpy_s(textFont.lfFaceName, _T("Courier New"));
	setbkmode(TRANSPARENT);
	settextcolor(0);
}