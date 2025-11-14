#pragma once
#include <easyx.h>
#include <tchar.h>

class Button
{
public:
	Button(IMAGE* img,IMAGE* img_pressed,int x_in, int y_in);
	void display(bool state);
	void display(bool state, TCHAR[]);
	bool isPressed();
	bool isClicked();
	void check();
private:
	LOGFONT textFont;
	int x;
	int y;
	IMAGE* Img;
	IMAGE* Img_pressed;
};