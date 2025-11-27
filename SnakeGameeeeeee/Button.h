#pragma once
#include <easyx.h>
#include <tchar.h>
#include "Tools.h"
class Button
{
public:
	Button(IMAGE* img,IMAGE* img_pressed,double x_in, double y_in);
	void display(TCHAR[]);

	void check(ExMessage* msg);
	bool isOn;
	bool isPressed;
	bool isClicked;
private:
	LOGFONT textFont;
	double x;
	double y;
	IMAGE* Img;
	IMAGE* Img_pressed;
	int width;
	int height;
};