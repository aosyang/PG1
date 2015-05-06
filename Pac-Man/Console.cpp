#include "Console.h"

namespace System
{

HANDLE Console::out = GetStdHandle(STD_OUTPUT_HANDLE);
WORD Console::defColors = Console::BackgroundColor() << 4 | Console::ForegroundColor();
HWND Console::hwnd = GetConsoleWindow();

WORD Console::ForegroundColor()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.wAttributes & 0x0F;
}

void Console::ForegroundColor(WORD attr)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	SetConsoleTextAttribute(out, info.wAttributes & 0xF0 | attr);
}

WORD Console::BackgroundColor()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return (info.wAttributes & 0xF0) >> 4;
}

void Console::BackgroundColor(WORD attr)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	SetConsoleTextAttribute(out, info.wAttributes & 0x0F | attr << 4);
}

void Console::ResetColor()
{
	SetConsoleTextAttribute(out, defColors);
}

int Console::WindowWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwSize.X;
}

int Console::WindowHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwSize.Y;
}

void Console::SetWindowSize(int columns, int rows)
{
	COORD c = GetLargestConsoleWindowSize(out);
	if (columns < 1 || columns > c.X)
		columns = c.X;
	if (rows < 1 || rows > c.Y)
		rows = c.Y;

	SMALL_RECT dim = { 0, 0, columns - 1, rows - 1 };
	SetConsoleWindowInfo(out, TRUE, &dim);
}

void Console::SetBufferSize(int columns, int rows)
{
	COORD c = { columns, rows };
	SetConsoleScreenBufferSize(out, c);
}

void Console::CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO curs;
	GetConsoleCursorInfo(out, &curs);
	if (curs.bVisible == TRUE && visible || curs.bVisible == FALSE && !visible)
		return;
	curs.bVisible = (visible) ? TRUE : FALSE;
	SetConsoleCursorInfo(out, &curs);
}

void Console::Clear()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);

	DWORD len = info.dwSize.X, num;
	COORD c = { 0, 0, };
	for (int i = 0; i < info.dwSize.Y; ++i)
	{
		c.Y = i;
		FillConsoleOutputAttribute(out, info.wAttributes, len, c, &num);
		FillConsoleOutputCharacter(out, ' ', len, c, &num);
	}

	SetCursorPosition(0, 0);
}

int Console::CursorLeft()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwCursorPosition.X;
}

int Console::CursorTop()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwCursorPosition.Y;
}

void Console::SetCursorPosition(int left, int top)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);

	left = max(left, 0);
	left = min(left, info.dwSize.X - 1);
	top = max(top, 0);
	top = min(top, info.dwSize.Y - 1);

	COORD cp = { left, top, };
	SetConsoleCursorPosition(out, cp);
}

void Console::Lock(bool lock)
{
	LockWindowUpdate(lock ? hwnd : nullptr);
}

void Console::EOLWrap(bool on)
{
	DWORD mode;
	GetConsoleMode(out, &mode);
	if (on)
		mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
	else
		mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
	SetConsoleMode(out, mode);
}

}
