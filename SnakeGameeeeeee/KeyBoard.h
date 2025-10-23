#pragma once

class KeyBoard
{
public:
	//返回1代表暂停
	bool getAndPause(char& dir);
	//返回1代表继续
	bool resume();
	//返回1代表退出
	bool escape();
	//清空输入缓冲区
	void flush();
};