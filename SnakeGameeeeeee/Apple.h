#pragma once

class Apple
{
private:
	int UnitX;
	int UnitY;
	int appleX;
	int appleY;
	int goldAppleX;
	int goldAppleY;
public:
	Apple(int unitx, int unity);
	void createApple(const int* x, const int* y, int length);
	void createGoldApple(const int* x, const int* y, int length);
	int counter = 0;


	const int AppleX() const;
	const int AppleY() const;
	const int GoldAppleX() const;
	const int GoldAppleY() const;
};