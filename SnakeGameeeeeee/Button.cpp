#include "Button.h"
#define UNIT 10

Button::Button(IMAGE* img, IMAGE* img_pressed, int x_in, int y_in)
	:Img(img), Img_pressed(img_pressed),x(x_in),y(y_in)
{
	textFont.lfHeight = 21;
	textFont.lfWeight = FW_REGULAR;
	textFont.lfItalic = 0;
	textFont.lfQuality = ANTIALIASED_QUALITY;
	_tcscpy_s(textFont.lfFaceName, "ROG Fonts");
	setbkmode(TRANSPARENT);
}
void Button::display(bool is_pressed)
{
	int w = Img->getwidth();
	int h = Img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT - h / 2, w, h,
		GetImageHDC(is_pressed ? Img_pressed : Img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
void Button::display(bool is_pressed,TCHAR text[])
{
	int w = Img->getwidth();
	int h = Img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT - h / 2, w, h,
		GetImageHDC(is_pressed ? Img_pressed : Img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	settextcolor(is_pressed ? 0xF8F8F8 : 0x000000);
	settextstyle(&textFont);
	outtextxy(x * UNIT - textwidth(text) / 2, y * UNIT - textheight(text) / 2 - 2, text);
}
bool Button::isPressed()
{
	
}
bool Button::isClicked()
{

}