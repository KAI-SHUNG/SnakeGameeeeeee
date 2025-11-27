#ifndef Image_H
#define Image_H
#include "easyx.h"

class Image
{
public:
	Image(IMAGE* img0, IMAGE* img1 = nullptr, IMAGE* img2 = nullptr, IMAGE* img3 = nullptr);
	void display(int time);
	//void display(double x, double y);
	//void display_c(double x, double y);
	void display(int x, int y, char dir);
	void display_t(int clock);
private:
	IMAGE* Img0;
	IMAGE* Img1;
	IMAGE* Img2;
	IMAGE* Img3;
};
#endif // !Image_H
