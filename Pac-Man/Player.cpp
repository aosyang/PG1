// TODO Part 1: Method Definitions for Player

#include "Player.h"

#include "Console.h"
using namespace System;

#include <iostream>
using std::cout;

Player::Player(MazeType maze, COORD coord, char* name)
{
	m_Coord = coord;

	int name_len = strlen(name) + 1;
	m_Name = new char[name_len];
	strcpy(m_Name, name);

	m_Score = 0;
	m_Lives = 3;

	m_HasPowerPellet = false;
	m_PowerPelletFrames = 0;

	Draw(maze);
}

Player::~Player()
{
	delete m_Name;
}

void Player::Move(MazeType maze, COORD coord)
{
	COORD newCoord;

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

	switch (maze[newCoord.Y][newCoord.X])
	{
	case MTL:
	case MTR:
	case MBL:
	case MBR:
	case MUD:
	case MLR:
	case MGD:
		// Invalid movement
		return;
	case MPP:
		m_Score += 50;
		m_HasPowerPellet = true;
		m_PowerPelletFrames = 25;
		break;
	case MDOT:
		m_Score += 10;
		break;
	default:
		break;
	}

	if (m_HasPowerPellet)
	{
		if (m_PowerPelletFrames == 0)
		{
			m_HasPowerPellet = false;
		}
		else
			m_PowerPelletFrames--;
	}

	ClearSpot(maze);

	m_Coord.X = newCoord.X;
	m_Coord.Y = newCoord.Y;

	Draw(maze);
}

void Player::Reset(MazeType maze, COORD coord)
{
	ClearSpot(maze);
	m_Coord.X = coord.X; m_Coord.Y = coord.Y;
	Draw(maze);
}

void Player::Draw(MazeType maze)
{
	maze[m_Coord.Y][m_Coord.X] = PAC;

	Console::SetCursorPosition(m_Coord.X, m_Coord.Y);
	Console::ForegroundColor(Yellow);
	cout << PAC;
}

void Player::ClearSpot(MazeType maze)
{
	maze[m_Coord.Y][m_Coord.X] = ' ';

	Console::SetCursorPosition(m_Coord.X, m_Coord.Y);
	cout << ' ';
}

void Player::DisplayHUD()
{
	Console::SetCursorPosition(0, 31);
	Console::ForegroundColor(Yellow);
	cout << m_Name << " | Score: " << m_Score << " | Lives: " << m_Lives;
}
