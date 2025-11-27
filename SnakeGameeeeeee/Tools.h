#ifndef Struct_H
#define Struct_H
#include <vector>
#include <easyx.h>
#pragma comment(lib,"MSIMG32.LIB")	//实现png透明通道必需的库
#define UNIT 10				//UNIT_SIZE每个单元格10x10像素
#define RATIO 2.5			//放大比例
#define MENUX 24			//菜单界面X共24单元格
#define MENUY 20			//菜单界面Y共20单元格
#define GAMEX 16			//游戏界面X共16单元格
#define GAMEY 20			//游戏界面Y共20单元格
#define BOARD 2				//计分板宽度2单元格
#define TIME_TOTAL 6000		//金苹果存在时间6000ms

struct Coordinate {
	int X;
	int Y;
	char Dir;
};

inline void putimage_alpha(double x, double y, IMAGE* img)
{
	if (img == nullptr) { return; }
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT, y * UNIT, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
inline void putimage_alpha_c(double x, double y, IMAGE* img)
{
	if (img == nullptr) { return; }
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x * UNIT - w / 2.0, y * UNIT - h / 2.0, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}
enum class SceneState { MENU, GAME, GAMEOVER, LEVEL, SOUND, EXIT };
enum class MenuState { PLAY, LEVEL, EXIT, COUNTER };
enum class LevelState { EASY, NORMAL, HARD, HELL, COUNTER };
enum class OverState { AGAIN, BACK, COUNTER };
#endif // !Struct_H