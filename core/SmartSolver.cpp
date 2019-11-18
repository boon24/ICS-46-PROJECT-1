#ifndef SMARTSOLVER_CPP
#define SMARTSOLVER_CPP

#include <iostream>
#include "SmartSolver.hpp"
#include <vector>
#include <random>
#include "Maze.hpp"
#include "Direction.hpp"
using namespace std;

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, SmartSolver, "SmartSolver(Required)");

SmartSolver::SmartSolver(){};
random_device newDevice;


void SmartSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();
    int cols = maze.getWidth();
    int rows = maze.getHeight();
    pair<int, int> startPoint = mazeSolution.getStartingCell();
    pair<int, int> endPoint = mazeSolution.getEndingCell();

    vector<vector<bool>> mazeStatus (cols, vector<bool>(rows,false));
    mazeStatus[startPoint.first][startPoint.second] = true;
    nextMove(maze,startPoint.first,startPoint.second,mazeStatus,endPoint,mazeSolution);
}


bool SmartSolver::nextMove(const Maze & maze ,int currentX, int currentY, vector<vector<bool>>& mazeStatus, pair<int,int> endPoint,MazeSolution& mazeSolution)
{
    if(currentX == endPoint.first and currentY ==endPoint.second)
    {
        return mazeSolution.isComplete();
    }


    vector <Direction> availableDirections = getAdjacentDirections(maze,currentX, currentY, mazeStatus);

    while (availableDirections.size() > 0)
    {

        int dir = getRandomDirection(availableDirections);
        if (availableDirections.at(dir) ==Direction::up) {
            mazeSolution.extend(Direction::up);
            mazeStatus[currentX][currentY - 1] = true;
            if(nextMove(maze, currentX, currentY - 1, mazeStatus,endPoint,mazeSolution))
                return true;
            mazeSolution.backUp();
        }

        if (availableDirections.at(dir) ==Direction::down) {
            mazeStatus[currentX][currentY + 1] = true;
            mazeSolution.extend(Direction::down);
            if(nextMove(maze, currentX, currentY + 1, mazeStatus,endPoint,mazeSolution))
                return true;
            mazeSolution.backUp();
        }
        if (availableDirections.at(dir)==Direction::left) {
            mazeStatus[currentX - 1][currentY] = true;
            mazeSolution.extend(Direction::left);
            if(nextMove(maze, currentX - 1, currentY, mazeStatus,endPoint,mazeSolution))
                return true;
            mazeSolution.backUp();
        }

        if (availableDirections.at(dir) ==Direction::right) {
            mazeStatus[currentX + 1][currentY] = true;
            mazeSolution.extend(Direction::right);
            if (nextMove(maze, currentX + 1, currentY, mazeStatus,endPoint,mazeSolution))
            	return true;
            mazeSolution.backUp();
        }


        availableDirections.clear();
        availableDirections = getAdjacentDirections(maze,currentX, currentY, mazeStatus);
    }

    return false;
}


vector<Direction> SmartSolver::getAdjacentDirections(const Maze & maze ,int currentX, int currentY,vector<vector<bool>>& mazeStatus)
{
    vector<Direction> availableDirections;
    if(!maze.wallExists(currentX, currentY, Direction::right) and mazeStatus[currentX+1][currentY]== false)
    {
        availableDirections.push_back(Direction::right);
    }

    if(!maze.wallExists(currentX, currentY, Direction::left) and mazeStatus[currentX-1][currentY]== false)
    {
        availableDirections.push_back(Direction::left);
    }

    if(!maze.wallExists(currentX, currentY, Direction::up) and mazeStatus[currentX][currentY-1]== false)
    {
        availableDirections.push_back(Direction::up);
    }

    if(!maze.wallExists(currentX, currentY, Direction::down) and mazeStatus[currentX][currentY+1]== false) {
        availableDirections.push_back(Direction::down);
    }
    return availableDirections;
}


int SmartSolver::getRandomDirection(vector<Direction> availableDirections)
{
    default_random_engine engine{newDevice()};
    int numDir = availableDirections.size();
    uniform_int_distribution<int> distribution{1,numDir};
    return distribution(engine)-1;
}

#endif
