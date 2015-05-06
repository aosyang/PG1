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

	Draw(maze);
}

Player::~Player()
{
	delete m_Name;
}

void Player::Move(MazeType maze, COORD coord)
{
	COORD newCoord;
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
		break;
	case MDOT:
		m_Score += 10;
		break;
	default:
		break;
	}

	ClearSpot(maze);

	m_Coord.X = newCoord.X;
	m_Coord.Y = newCoord.Y;

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
	cout << m_Name << " | Score: " << m_Score << " | Lives: " << m_Lives;
}
