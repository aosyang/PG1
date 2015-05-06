// TODO Part 2: Class Declaration for Ghost

#include "globals.h"

#include "Console.h"
using namespace System;

class Ghost
{
public:
	Ghost(ConsoleColor color, COORD start);

	void Move(MazeType maze, Ghost** ghosts);
	void Draw();

	//void Kill(MazeType maze);
	//void Reset(MazeType maze, COORD coord);

	//inline COORD GetPos() { return m_Coord; }
private:
	void TryResetSpot(MazeType maze, Ghost** ghosts);
	void ClearSpot(MazeType maze);

	COORD			m_Coord;
	ConsoleColor	m_Color;
	int				m_AvoidMove;
	bool			m_InsideCage;
};
