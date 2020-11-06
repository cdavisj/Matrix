#include "Console.h"

#include <Windows.h>

namespace console
{
    void gotoxy(const short& x, const short& y)
    {
        HANDLE handle;
        COORD coord;

        handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (handle == INVALID_HANDLE_VALUE)
            return;

        coord = { x, y };

        SetConsoleCursorPosition(handle, coord);
    }

    void showCursor(const bool& flag)
    {
        HANDLE handle;
        CONSOLE_CURSOR_INFO consoleCursorInfo;

        handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (handle == INVALID_HANDLE_VALUE)
            return;

        GetConsoleCursorInfo(handle, &consoleCursorInfo);

        consoleCursorInfo.bVisible = flag;

        SetConsoleCursorInfo(handle, &consoleCursorInfo);
    }

    void clearScreen()
    {
        HANDLE handle;
        CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
        DWORD count;
        DWORD cellCount;
        COORD origin;

        origin = { 0, 0 };

        handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (handle == INVALID_HANDLE_VALUE)
            return;

        if (!GetConsoleScreenBufferInfo(handle, &consoleScreenBufferInfo))
            return;

        cellCount = consoleScreenBufferInfo.dwSize.X * consoleScreenBufferInfo.dwSize.Y;

        if (!FillConsoleOutputCharacter(handle, (TCHAR)' ', cellCount, origin, &count))
            return;

        if (!FillConsoleOutputAttribute(handle, consoleScreenBufferInfo.wAttributes,
            cellCount, origin, &count))
            return;

        SetConsoleCursorPosition(handle, origin);
    }
}
