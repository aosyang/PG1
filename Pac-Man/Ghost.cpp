// TODO Part 2: Method Definitions for Ghost

#include "Ghost.h"

#include "Console.h"
using namespace System;

#include <iostream>
using std::cout;

Ghost::Ghost(ConsoleColor color, COORD start)
{
	m_Coord = start;
	m_Color = color;
	m_ScaredColor = White;
	m_AvoidMove = -1;
	m_InsideCage = (color != Red);

	Draw(false);
}

void Ghost::Move(MazeType maze, Ghost** ghosts, bool scared)
{
	int dir;
	COORD newCoord;

	// When scared, ghost moves once two frames
	if (scared && m_ScaredColor == White)
	{
		Draw(scared);
		return;
	}

	while (true)
	{
		// Generate random direction for moving. When ghost in cage,
		// give 5 out of 8 chance for moving up.
		int all_dir = m_InsideCage ? 8 : 4;
		dir = rand() % all_dir;
		while (dir == m_AvoidMove || (m_AvoidMove == 0 && dir > 3))
		{
			dir = rand() % all_dir;
		}

		COORD coord;
		switch (dir)
		{
		case 0:
			coord.X = 0; coord.Y = -1;
			break;
		case 1:
			coord.X = 2; coord.Y = 0;
			break;
		case 2:
			coord.X = 0; coord.Y = 1;
			break;
		case 3:
			coord.X = -2; coord.Y = 0;
			break;
		default:
			coord.X = 0; coord.Y = -1;
			break;
		}

		// Handle wrap
		if (m_Coord.Y == 14)
		{
			if (m_Coord.X == 1 && coord.X == -2)
			{
				coord.X = 52;
			}
			
			if (m_Coord.X == 53 && coord.X == 2)
			{
				coord.X = -52;
			}
		}

		newCoord.X = m_Coord.X + coord.X;
		newCoord.Y = m_Coord.Y + coord.Y;

		bool validMove = true;

		switch (maze[newCoord.Y][newCoord.X])
		{
		case MTL:
		case MTR:
		case MBL:
		case MBR:
		case MUD:
		case MLR:
			validMove = false;
			break;
		case MGD:
			if (!m_InsideCage)
				validMove = false;
			else
				m_InsideCage = false;
			break;
		}

		if (validMove)
		{
			// Avoid moving in the opposite of current direction
			m_AvoidMove = (dir < 4) ? dir : 0;
			m_AvoidMove += 2;
			m_AvoidMove %= 4;

			TryResetSpot(maze, ghosts);

			m_Coord = newCoord;

			Draw(scared);

			break;
		}
	}
}

void Ghost::Draw(bool scared)
{
	Console::SetCursorPosition(m_Coord.X, m_Coord.Y);

	ConsoleColor color = m_Color;
	if (scared)
	{
		color = m_ScaredColor;
		m_ScaredColor = (m_ScaredColor == White) ? Blue : White;
	}

	Console::ForegroundColor(color);
	cout << MGH;
}

void Ghost::Kill(MazeType maze)
{
	ClearSpot(maze);
	m_Coord.X = 27; m_Coord.Y = 14;
	Draw(false);

	m_InsideCage = true;
	m_AvoidMove = -1;
}

void Ghost::Reset(MazeType maze, COORD coord)
{
	m_AvoidMove = -1;
	m_InsideCage = (m_Color != Red);
	ClearSpot(maze);
	m_Coord.X = coord.X; m_Coord.Y = coord.Y;
}

void Ghost::TryResetSpot(MazeType maze, Ghost** ghosts)
{
	for (int i = 0; i < NUM_GHOSTS; i++)
	{
		if (ghosts[i] == this)
			continue;

		if (CoordsEqual(ghosts[i]->m_Coord, this->m_Coord))
			return;
	}

	ClearSpot(maze);
}

void Ghost::ClearSpot(MazeType maze)
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