#ifndef Struct_H
#define Struct_H
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