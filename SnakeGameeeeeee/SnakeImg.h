#ifndef Image_H
#define Image_H
#include <easyx.h>
class SnakeImg
{
public:
	SnakeImg(IMAGE* img0, IMAGE* img1, IMAGE* img2, IMAGE* img3);
	void display(int x, int y, char dir);
private:
	IMAGE* Img0;
	IMAGE* Img1;
	IMAGE* Img2;
	IMAGE* Img3;
};
#endif // !Image_H