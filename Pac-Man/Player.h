// TODO Part 1: Class Declaration for Player

#include "globals.h"

class Fruit;

class Player
{
public:
	Player(MazeType maze, COORD coord, char* name, int dotCount);
	~Player();

	void Move(MazeType maze, COORD coord, Fruit* fruit);

	void DisplayHUD();

	void Reset(MazeType maze, COORD coord);

	inline void Kill() { m_Lives--; }
	inline COORD GetPos() { return m_Coord; }
	inline int GetLives() { return m_Lives; }
	inline bool GetPowerPellet() { return m_HasPowerPellet; }
	inline void GhostKilled() { m_Score += 200; }
	inline int GetDotCount() { return m_DotCount; }
private:
	void Draw(MazeType maze);
	void ClearSpot(MazeType maze);

	COORD	m_Coord;
	char*	m_Name;
	int		m_Score;
	int		m_Lives;
	int		m_DotCount;
	bool	m_HasPowerPellet;
	int		m_PowerPelletFrames;
};
