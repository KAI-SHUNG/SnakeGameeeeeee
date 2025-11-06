#pragma once
enum Menu { BEGIN, EXIT };
class Keyboard
{
public:
	//返回1代表enter
	void menu(Menu& state);
	//返回1代表暂停
	bool game(char& dir);
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