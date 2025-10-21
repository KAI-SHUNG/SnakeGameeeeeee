#pragma once

class Apple
{
private:
	int UnitX;
	int UnitY;
	int appleX;
	int appleY;
public:
	Apple(int unitx, int unity);
	void createApple(const int* x, const int* y, int length);

	const int AppleX();
	const int AppleY();
};