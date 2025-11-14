#include "Button.h"
#define UNIT 10
#include <iostream>
Button::Button(IMAGE* img, IMAGE* img_pressed, int x_in, int y_in)
	:Img(img), Img_pressed(img_pressed), x(x_in), y(y_in), isPressed(0), isClicked(0)
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
void Button::display(bool is_pressed,TCHAR text[])
{
	AlphaBlend(GetImageHDC(NULL), x * UNIT - width / 2, y * UNIT - height / 2, width, height,
		GetImageHDC(is_pressed ? Img_pressed : Img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	settextcolor(is_pressed ? 0xF8F8F8 : 0x000000);
	settextstyle(&textFont);
	outtextxy(x * UNIT - textwidth(text) / 2, y * UNIT - textheight(text) / 2 - 2, text);
}
void Button::check(ExMessage* msg)
{
	std::cout << "Checked.\n"
		<< msg->x << ' ' << msg->y << std::endl
		<< x * UNIT * 2.5 << ' ' << y * UNIT * 2.5 <<std::endl;
	if (msg->lbutton)
	{
		std::cout << "Clicked\n";
	}
	
	if (msg->x >= x * UNIT  && msg->x <= x * UNIT  + width &&
		msg->y >= y * UNIT  && msg->y <= y * UNIT  + height)
	{
		std::cout << "Enter if4\n";
		if (msg->message == WM_LBUTTONDOWN)
		{
			if (isPressed)
			{
				isClicked = true;
			}
			else
			{
				isPressed = true;
			}
		}
		else
		{
			isPressed = false;
		}
	}
}
void Button::reset()
{
	isPressed = 0;
	isClicked = 0;
}