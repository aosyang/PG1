// TODO Part 1: Method Definitions for Player

#include "Player.h"
#include "Fruit.h"

#include "AudioSystem.h"

#include "Console.h"
using namespace System;

#include <iostream>
using std::cout;

Player::Player(MazeType maze, COORD coord, char* name, int dotCount)
{
	m_Coord = coord;

	int name_len = strlen(name) + 1;
	m_Name = new char[name_len];
	strcpy(m_Name, name);

	m_Score = 0;
	m_Lives = 3;

	m_DotCount = dotCount;

	m_HasPowerPellet = false;
	m_PowerPelletFrames = 0;

	m_MovingDir = -1;

	Draw(maze);
}

Player::~Player()
{
	delete [] m_Name;
}

void Player::Move(MazeType maze, COORD coord, Fruit* fruit)
{
	COORD newCoord;
	int newDir = -1;

	if (coord.Y == -1)
		newDir = 0;
	else if (coord.X == 2)
		newDir = 1;
	else if (coord.Y == 1)
		newDir = 2;
	else if (coord.X == -2)
		newDir = 3;

	// Try moving in input direction
	if (newDir == -1 || !TryMoving(maze, coord))
	{
		switch (m_MovingDir)
		{
		case 0:
			coord.X = 0; coord.Y = -1;	// up
			break;
		case 1:
			coord.X = 2; coord.Y = 0;	// right
			break;
		case 2:
			coord.X = 0; coord.Y = 1;	// down
			break;
		case 3:
			coord.X = -2; coord.Y = 0;	// left
			break;
		default:
			break;
		}

		// If failed, try moving in original direction
		if (!TryMoving(maze, coord))
		{
			m_MovingDir = -1;
			return;
		}

		newDir = m_MovingDir;
	}

	newCoord.X = m_Coord.X + coord.X;
	newCoord.Y = m_Coord.Y + coord.Y;

	if (CoordsEqual(newCoord, fruit->GetPos()) && fruit->IsShown())
	{
		fruit->Kill();
		m_Score += 100;
		AudioSystem::GetInstance()->Play(GAME_SOUND_EATFRUIT);
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

	m_MovingDir = newDir;
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

bool Player::TryMoving(MazeType maze, COORD& coord)
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
		return false;
	case MPP:
		m_Score += 50;
		m_HasPowerPellet = true;
		m_PowerPelletFrames = 25;
		break;
	case MDOT:
		m_Score += 10;
		m_DotCount--;
		AudioSystem::GetInstance()->Play(GAME_SOUND_COININ);
		break;
	default:
		break;
	}

	return true;
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
