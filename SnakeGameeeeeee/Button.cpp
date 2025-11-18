#include "Button.h"
#define UNIT 10
#include <iostream>
Button::Button(IMAGE* img, IMAGE* img_pressed, double x_in, double y_in)
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
void Button::display(TCHAR text[])
{
	putimage_alpha_c(x, y, isPressed ? Img_pressed : Img);
	settextcolor(isOn ? 0xF8F8F8 : 0x000000);
	settextstyle(&textFont);
	outtextxy(x * UNIT - textwidth(text) / 2, y * UNIT - textheight(text) / 2 - 2, text);
}
void Button::check(ExMessage* msg)
{
	if (msg->x >= (x * UNIT - width / 2.0) * 2.5 && msg->x <= (x * UNIT + width / 2.0) * 2.5  &&
		msg->y >= (y * UNIT - height / 2.0) * 2.5 && msg->y <= (y * UNIT + height / 2.0) * 2.5 )
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