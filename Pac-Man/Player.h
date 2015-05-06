// TODO Part 1: Class Declaration for Player

#include "globals.h"

typedef char MazeType[MAZE_ROWS][MAZE_COLS];

class Player
{
public:
	Player(MazeType maze, COORD coord, char* name);
	~Player();

	void Move(MazeType maze, COORD coord);

	void DisplayHUD();

private:
	void Draw(MazeType maze);
	void ClearSpot(MazeType maze);

	COORD	m_Coord;
	char*	m_Name;
	int		m_Score;
	int		m_Lives;
};
