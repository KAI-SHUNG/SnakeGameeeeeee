#pragma once
#include <easyx.h>

class Button
{
public:
	Button(IMAGE* img,IMAGE* img_pressed,int x_in, int y_in);
	void display(bool state);
	bool isPressed();
	bool isClicked();
	
private:
	int x;
	int y;
	IMAGE* Img;
	IMAGE* Img_pressed;
};