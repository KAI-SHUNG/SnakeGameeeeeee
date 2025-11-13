#ifndef Image_H
#define Image_H
#include <easyx.h>
//#pragma comment(lib,"MSIMG32.LIB")	//实现png透明通道必需的库

class Image
{
public:
	Image();
	Image(IMAGE* img);
	void display(int x, int y);

private:
	IMAGE* Img;
};
#endif // !Image_H