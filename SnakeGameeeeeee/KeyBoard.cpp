#include "KeyBoard.h"
#include <windows.h>

bool KeyBoard::getAndPause(char& dir)
{
    if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000)
    {
        dir = 'w';
        return 0;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
    {
        dir = 'a';
        return 0;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000)
    {
        dir = 's';
        return 0;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000)
    {
        dir = 'd';
        return 0;
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        return 1;
    }
    return 0;
}

bool KeyBoard::resume()
{
    return GetAsyncKeyState(VK_SPACE) & 0x8000;
}

bool KeyBoard::escape()
{
    return GetAsyncKeyState(VK_ESCAPE) & 0x8000;
}

void KeyBoard::flush()
{
    MSG m;
    while (PeekMessage(&m, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
    {
        ;
    }
}