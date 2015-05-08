#include "Console.h"
#include <iostream>
using namespace std;

namespace System
{

WORD Console::defColors = 0;

WORD Console::ForegroundColor()
{
	return 0;
}

void Console::ForegroundColor(WORD attr)
{
	if (attr < 10)
		cout << "\033[" << attr + 30 << "m";
	else
		cout << "\033[" << attr + 20 << ";1m";
}

WORD Console::BackgroundColor()
{
	return 0;
}

void Console::BackgroundColor(WORD attr)
{
}

void Console::ResetColor()
{
	cout << "\033[0m";
}

int Console::WindowWidth()
{
	return 0;
}

int Console::WindowHeight()
{
	return 0;
}

void Console::SetWindowSize(int columns, int rows)
{
}

void Console::SetBufferSize(int columns, int rows)
{
}

void Console::CursorVisible(bool visible)
{
}

void Console::Clear()
{
}

int Console::CursorLeft()
{
	return 0;
}

int Console::CursorTop()
{
	return 0;
}

void Console::SetCursorPosition(int left, int top)
{
	cout << "\033[" << top+1 << ";" << left+1 << "H";
}

void Console::Lock(bool lock)
{
}

void Console::EOLWrap(bool on)
{
}

}
