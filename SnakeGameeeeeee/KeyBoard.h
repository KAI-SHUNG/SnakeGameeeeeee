#pragma once
enum class MenuState { PLAY, EXIT };
enum class GameoverState { AGAIN, EXIT };
class Keyboard
{
public:
	//修改Menu状态
	void menu(MenuState& state);
	//修改dir
	void move(char& dir);
	//修改Gameover后状态
	void gameover(GameoverState& state);
	bool up();
	bool left();
	bool down();
	bool right();
	bool enter();
	bool space();
	bool escape();
	//清空输入缓冲区
	void flush();
};