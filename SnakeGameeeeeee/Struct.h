#ifndef Struct_H
#define Struct_H

#define UNIT 10				//UNIT_SIZE每个单元格10x10像素
#define RATIO 2.5			//放大比例
#define MENUX 24			//菜单界面X共24单元格
#define MENUY 20			//菜单界面Y共20单元格
#define GAMEX 16			//游戏界面X共16单元格
#define GAMEY 20			//游戏界面Y共20单元格
#define BOARD 2				//计分板宽度2单元格
#define TIME_TOTAL 6000		//金苹果存在时间6000ms

#define BKCOLOR 0xF0FFF0	//背景颜色
#define BOARDCOLOR 0x66B2FF	//计分板颜色
#define LINECOLOR 0x0066CC	//计分板边框颜色
#define TEXTCOLOR 0x003366	//字体颜色

#include <vector>
struct Coordinate {
	int X;
	int Y;
	char Dir;
};
enum class SceneState { MENU, GAME, GAMEOVER, MODE, SOUND, EXIT };
enum class MenuState { PLAY, EXIT };
enum class GameoverState { AGAIN, BACK };
#endif // !Struct_H