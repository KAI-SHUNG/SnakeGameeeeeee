#include "Keyboard.h"
#include <windows.h>

void Keyboard::menu(Menu& state)
{
    if (up())
    {
        state = Menu((state - 1 + 2) % 2);
        return;
    }
    else if (down())
    {
        state = Menu((state + 1) % 2);
        return;
    }
    return;
}
bool Keyboard::game(char& dir)
{
    if (up())
    {
        dir = 'w';
        return 0;
    }
    else if (left())
    {
        dir = 'a';
        return 0;
    }
    else if (down())
    {
        dir = 's';
        return 0;
    }
    else if (right())
    {
        dir = 'd';
        return 0;
    }
    else if (space() || escape())
    {
        return 1;
    }
    return 0;
}

bool Keyboard::up()
{
    return GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000;
}
bool Keyboard::left()
{
    return GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000;
}
bool Keyboard::down()
{
    return GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000;
}
bool Keyboard::right()
{
    return GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000;
}
bool Keyboard::enter()
{
    return GetAsyncKeyState(VK_RETURN) & 0x8000;
}
bool Keyboard::space()
{
    return GetAsyncKeyState(VK_SPACE) & 0x8000;
}
bool Keyboard::escape()
{
    return GetAsyncKeyState(VK_ESCAPE) & 0x8000;
}

void Keyboard::flush()
{
    MSG m;
    while (PeekMessage(&m, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
    {
        GetMessage(&m, NULL,WM_KEYFIRST, WM_KEYLAST);
    }
}