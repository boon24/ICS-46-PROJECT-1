#include "MazeGen.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MazeGen, "MazeGen (Required)");
std::random_device device;


struct Cell {
	int x;
	int y;
};

//int maze[10][10];
typedef vector<vector<int>> MazeStat;
MazeGen::MazeGen(){};


Direction chooseRandomDirection(const vector<Direction> &directions) {
	int size = directions.size();
	std::default_random_engine engine{device()};
	std::uniform_int_distribution<int> distribution{0,size - 1};
	return directions[distribution(engine)];
}


vector<Direction> getAdjacentWalls(const Cell currentCell, Maze &maze, MazeStat &mazeStatus) {
	vector<Direction> result;

	int row = maze.getHeight();
	int col = maze.getWidth();

	if(currentCell.x >=0 and (currentCell.x+1)<col and mazeStatus[currentCell.x+1][currentCell.y]== 0) {
        result.push_back(Direction::right);
    }

    if((currentCell.x -1) >=0 and currentCell.x<col and mazeStatus[currentCell.x-1][currentCell.y]== 0) {
        result.push_back(Direction::left);
    }

    if((currentCell.y-1) >=0 and currentCell.y<row and mazeStatus[currentCell.x][currentCell.y-1]== 0) {
        result.push_back(Direction::up);
    }

    if(currentCell.y >=0 and (currentCell.y+1)<row and mazeStatus[currentCell.x][currentCell.y+1]== 0) {
        result.push_back(Direction::down);
    }
  
	return result;
}



void markAsVisited(MazeStat &mazeStatus, Cell &currentCell) {
	mazeStatus[currentCell.x][currentCell.y] = 1;
}

Direction pickRandomWall(vector<Direction> &adjacentWalls) {
	int size = adjacentWalls.size();
	std::default_random_engine engine{device()};
	std::uniform_int_distribution<int> distribution{1,size};
	return adjacentWalls[distribution(engine) - 1];
}

//Recursive
void nextMove(Maze &maze, MazeStat &mazeStatus,const Cell &currentCell) {
	vector<Direction> adjacentWalls = getAdjacentWalls(currentCell, maze, mazeStatus);


	while (adjacentWalls.size() > 0) {
		Direction nextDirection = pickRandomWall(adjacentWalls);
		
		Cell nextCell;
		if(nextDirection == Direction::right) {
			maze.removeWall(currentCell.x, currentCell.y, nextDirection);
			nextCell.x = currentCell.x + 1;
			nextCell.y = currentCell.y;
			markAsVisited(mazeStatus, nextCell);
			nextMove(maze, mazeStatus, nextCell);
		} if(nextDirection == Direction::left) {
			maze.removeWall(currentCell.x, currentCell.y, nextDirection);
			nextCell.x = currentCell.x - 1;
			nextCell.y = currentCell.y;
			markAsVisited(mazeStatus, nextCell);
			nextMove(maze, mazeStatus, nextCell);

		} if(nextDirection == Direction::down) {
			maze.removeWall(currentCell.x, currentCell.y, nextDirection);
			nextCell.x = currentCell.x;
			nextCell.y = currentCell.y + 1;
			markAsVisited(mazeStatus, nextCell);
			nextMove(maze, mazeStatus, nextCell);

		} if(nextDirection == Direction::up) {
			maze.removeWall(currentCell.x, currentCell.y, nextDirection);
			nextCell.x = currentCell.x;
			nextCell.y = currentCell.y - 1;
			markAsVisited(mazeStatus, nextCell);
			nextMove(maze, mazeStatus, nextCell);

		}
		

		adjacentWalls.clear();
		adjacentWalls = getAdjacentWalls(currentCell, maze, mazeStatus);

	}
}

void MazeGen::generateMaze(Maze& maze)
{
	maze.addAllWalls(); //Adds all the walls to begin with

	Cell currentCell;
	currentCell.x = 0;
	currentCell.y = 0;

	int rows = maze.getHeight();
	int cols = maze.getWidth();	

	MazeStat mazeStatus(cols, std::vector<int>(rows, 0));

	//Marks initial top-left(0,0) cell as visited.
	markAsVisited(mazeStatus, currentCell);
	nextMove(maze, mazeStatus, currentCell);
}

