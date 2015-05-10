
#include "globals.h"

class Fruit
{
public:
	Fruit(MazeType maze);

	void Draw(MazeType maze);

	inline bool IsShown() { return m_Show; }
	inline COORD GetPos() { return m_Coord;  }
	inline void Kill() { m_TimeCountdown = 0; }

private:
	void ClearSpot(MazeType maze);

private:
	bool	m_AvailableCoord[MAZE_ROWS][MAZE_COLS];
	int		m_TimeCountdown;
	COORD	m_Coord;
	bool	m_Show;
};