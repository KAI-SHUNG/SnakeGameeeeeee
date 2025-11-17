#pragma once
#include <easyx.h>
#include <tchar.h>
#include "Tools.h"
class Button
{
public:
	Button(IMAGE* img,IMAGE* img_pressed,int x_in, int y_in);
	//void display(bool state);
	void display(TCHAR[]);

	void check(ExMessage* msg);
	bool isOn;
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