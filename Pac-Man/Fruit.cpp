
#include "Fruit.h"
#include "Console.h"
using namespace System;

#include <iostream>
using std::cout;

Fruit::Fruit(MazeType maze)
{
	// Build available coord table for fruit
	for (int y = 0; y < MAZE_ROWS; y++)
		for (int x = 0; x < MAZE_COLS; x++)
		{
			m_AvailableCoord[y][x] = (maze[y][x] == MDOT) || (maze[y][x] == MPP);
		}

	m_TimeCountdown = 20;
	m_Show = false;
	Draw(maze);
}

void Fruit::Draw(MazeType maze)
{
	if (m_TimeCountdown <= 0)
	{
		if (!m_Show)
		{
			int x, y;
			do
			{
				x = (rand() % 27) * 2 + 1;
				y = rand() % 30 + 1;
			} while (m_AvailableCoord[y][x] != true);

			m_Coord.X = x;
			m_Coord.Y = y;

			m_TimeCountdown = 40;
			m_Show = true;
		}
		else
		{
			m_TimeCountdown = 20;
			m_Show = false;
			ClearSpot(maze);
		}
	}
	else
	{
		m_TimeCountdown--;
	}

	if (m_Show)
	{
		Console::SetCursorPosition(m_Coord.X, m_Coord.Y);
		Console::ForegroundColor(Red);
		cout << MFR;
	}
}

void Fruit::ClearSpot(MazeType maze)
{
	Console::SetCursorPosition(m_Coord.X, m_Coord.Y);

	if (MPP == maze[m_Coord.Y][m_Coord.X])
		Console::ForegroundColor(Green);
	else if (MDOT == maze[m_Coord.Y][m_Coord.X] || MGD == maze[m_Coord.Y][m_Coord.X])
		Console::ForegroundColor(White);
	else
		Console::ForegroundColor(Blue);
	cout << maze[m_Coord.Y][m_Coord.X];

}