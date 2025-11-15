#include "Button.h"
#define UNIT 10
#include <iostream>
Button::Button(IMAGE* img, IMAGE* img_pressed, int x_in, int y_in)
	:Img(img), Img_pressed(img_pressed), x(x_in), y(y_in), isOn(0),isPressed(0), isClicked(0)
{
	width = Img->getwidth();
	height = Img->getheight();

	textFont.lfHeight = 21;
	textFont.lfWeight = FW_REGULAR;
	textFont.lfItalic = 0;
	textFont.lfQuality = ANTIALIASED_QUALITY;
	_tcscpy_s(textFont.lfFaceName, "ROG Fonts");
	setbkmode(TRANSPARENT);
}
void Button::display(bool is_pressed)
{
	AlphaBlend(GetImageHDC(NULL), x * UNIT - width / 2, y * UNIT - height / 2, width, height,
		GetImageHDC(is_pressed ? Img_pressed : Img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
void Button::display(TCHAR text[])
{
	AlphaBlend(GetImageHDC(NULL), x * UNIT - width / 2, y * UNIT - height / 2, width, height,
		GetImageHDC(isPressed ? Img_pressed : Img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	settextcolor(isOn ? 0xF8F8F8 : 0x000000);
	settextstyle(&textFont);
	outtextxy(x * UNIT - textwidth(text) / 2, y * UNIT - textheight(text) / 2 - 2, text);
}
void Button::check(ExMessage* msg)
{
	//std::cout << "Checked.\n"
	//	<< msg->x << ' ' << msg->y << std::endl
	//	<< (x * UNIT - width / 2) * 2.5 << ' ' << (y * UNIT - height / 2) * 2.5 << std::endl;
	if (msg->x >= (x * UNIT - width / 2) * 2.5 && msg->x <= (x * UNIT + width / 2) * 2.5  &&
		msg->y >= (y * UNIT - height / 2) * 2.5 && msg->y <= (y * UNIT + height / 2) * 2.5 )
	{
		isOn = true;
		if (msg->message == WM_LBUTTONDOWN)
		{
			isPressed = true;
		}
		if (msg->message == WM_LBUTTONUP)
		{
			isPressed = false;
			isClicked = true;
		}
	}
	else
	{
		isOn = false;
		isPressed = false;
	}
}