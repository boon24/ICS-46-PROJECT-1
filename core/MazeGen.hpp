#ifndef MAZEGEN_HPP
#define MAZEGEN_HPP

#include "MazeGenerator.hpp"

class MazeGen: public MazeGenerator
{

public:
	MazeGen();

	virtual void generateMaze(Maze& maze);
	
};

#endif