#define _CRT_SECURE_NO_WARNINGS 1
#include <tchar.h>
#include<stdio.h>
#include<graphics.h>
int main()
{
	initgraph(1000, 640, SHOWCONSOLE);//创建一个窗口
	setbkcolor(WHITE);//设置窗口颜色
	cleardevice();//刷新一下，防止窗口颜色不变
	while (1)//不断处理事务，需要循环
	{
		if (MouseHit())//判断是否有鼠标信息
		{
			settextcolor(BLACK);//默认为白色
			cleardevice();//每次显示左右键按下后清屏
			MOUSEMSG msg = GetMouseMsg();//接收鼠标信息
			printf("坐标为（%d,%d）", msg.x, msg.y);//显示鼠标坐标
			switch (msg.uMsg)//uMsg判断鼠标信息是什么信息(左键信息或者右键信息)
			{
			case WM_LBUTTONDOWN://左键按下
				if (msg.x > 0 && msg.x < 250 && msg.y>0 && msg.y < 250)//在特定范围内显示
				{
					printf("星辰\n");
				}
				outtextxy(400, 400, _T("Left"));
				break;
			case WM_RBUTTONDOWN://右键按下
				if (msg.x > 0 && msg.x < 250 && msg.y>0 && msg.y < 250)
				{
					printf("星辰\n");
				}
				outtextxy(400, 400, _T("Right"));
				break;
			}
		}
	}
	getchar();//防止闪退
	closegraph();//关闭窗口
	return 0;
}