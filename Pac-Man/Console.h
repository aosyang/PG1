#pragma once

#ifdef _WIN32

	#include <windows.h>

#else

	typedef unsigned int WORD;

#endif

namespace System
{

// Colors - can be used as Foreground or Background
#ifdef _WIN32

enum ConsoleColor
{
	Black		= 0,
	DarkBlue	= FOREGROUND_BLUE,
	DarkGreen	= FOREGROUND_GREEN,
	DarkCyan	= FOREGROUND_GREEN | FOREGROUND_BLUE,
	DarkRed		= FOREGROUND_RED,
	DarkMagenta	= FOREGROUND_RED | FOREGROUND_BLUE,
	DarkYellow	= FOREGROUND_RED | FOREGROUND_GREEN,
	Gray		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	DarkGray	= FOREGROUND_INTENSITY,
	Blue		= FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Green		= FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	Cyan		= FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Red			= FOREGROUND_RED | FOREGROUND_INTENSITY,
	Magenta		= FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Yellow		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	White		= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

#else

enum ConsoleColor
{
	Black		= 0,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

#endif

class Console
{
private:
	// Data members
#ifdef _WIN32
	static HANDLE out;
	static HWND hwnd;
#endif
	static WORD defColors;

public:
	// Get the current foreground color
	static WORD ForegroundColor();

	// Change the foreground color
	static void ForegroundColor(WORD attr);

	// Get the current background color
	static WORD BackgroundColor();

	// Change the background color
	static void BackgroundColor(WORD attr);

	// Set the colors back to the defaults (usually gray on black)
	static void ResetColor();
	
	// Get the width of the window in cells (characters)
	static int WindowWidth();

	// Get the height of the window in cells (characters)
	static int WindowHeight();

	// Change the size of the window
	static void SetWindowSize(int columns, int rows);

	// Change the size of the buffer
	// Should call this whenever you change the window size
	static void SetBufferSize(int columns, int rows);

	// Get the current column of the cursor
	static int CursorLeft();

	// Get the current row of the cursor
	static int CursorTop();

	// Change the position of the cursor
	static void SetCursorPosition(int left, int top);

	// Clear the screen
	static void Clear();

	// Set the visibility of the cursor
	static void CursorVisible(bool visible);

	// For animation and/or to reduce flickering
	static void Lock(bool lock);

	// Do or don't scroll when printing to the lower-right cell.
	static void EOLWrap(bool on);
};

}
