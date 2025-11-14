#ifndef Struct_H
#define Struct_H
#include <vector>
struct Coordinate {
	int X;
	int Y;
	char Dir;
};
enum class SceneState { MENU, GAME, EXIT };
enum class MenuState { PLAY, EXIT };
enum class GameoverState { AGAIN, EXIT };
#endif // !Coordinate_H