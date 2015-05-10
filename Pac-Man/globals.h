#ifndef GLOBALS_H
#define GLOBALS_H

#include <windows.h>

// Helper function to create a coord and assign values to x and y (otherwise they would be garbage).
inline COORD CreateCoord(short x, short y)
{
	COORD pos = { x, y };
	return pos;
}

// Helper function to see if 2 coords are equal (can't use == with coords).
inline bool CoordsEqual(const COORD &a, const COORD &b)
{
	return a.X == b.X && a.Y == b.Y;
}

#define MAZE_ROWS 31
#define MAZE_COLS 55

typedef char MazeType[MAZE_ROWS][MAZE_COLS];

#define NUM_GHOSTS 4

// Warp coordinates.
#define WARP_LEFT_X 1
#define WARP_RIGHT_X 53
#define WARP_Y 14

// **************************************
//              Maze symbols
// **************************************

// MazeTopLeft
#define MTL (char)218

// MazeTopRight
#define MTR (char)191

// MazeBottomLeft
#define MBL (char)192

// MazeBottomRight
#define MBR (char)217

// MazeUpDown
#define MUD (char)179

// MazeLeftRight
#define MLR (char)196

// MazeGhostDoor
#define MGD '-'

// MazePowerPellet
#define MPP '0'

// MazeDot
#define MDOT 'o'

// MazeFruit
#define MFR '*'

// MazeGhost
#define MGH (char)1

// Player
#define PAC '<'

#endif
