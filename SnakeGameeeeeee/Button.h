#pragma once
#include <easyx.h>
#include <tchar.h>
#include "Struct.h"
class Button
{
public:
	Button(IMAGE* img,IMAGE* img_pressed,int x_in, int y_in);
	void display(bool state);
	void display(bool state, TCHAR[]);

	void check(ExMessage* msg);
	void reset();
	bool isPressed;
	bool isClicked;
private:
	LOGFONT textFont;
	int x;
	int y;
	IMAGE* Img;
	IMAGE* Img_pressed;
	int width;
	int height;
};