#pragma once
#include <easyx.h>

class Button
{
public:
	Button(IMAGE& img,IMAGE& img_pressed,int x, int y);
	void display();
	bool isPressed();
	bool isClicked();
};