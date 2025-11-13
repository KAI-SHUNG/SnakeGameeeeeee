#include "Button.h"
#define UNIT 10

Button::Button(IMAGE* img, IMAGE* img_pressed, int x_in, int y_in)
	:Img(img), Img_pressed(img_pressed),x(x_in),y(y_in)
{

}
void Button::display(bool is_pressed)
{
	int w = Img->getwidth();
	int h = Img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2, y * UNIT, w, h,
		GetImageHDC(is_pressed ? Img_pressed : Img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
bool Button::isPressed()
{
	
}
bool Button::isClicked()
{

}