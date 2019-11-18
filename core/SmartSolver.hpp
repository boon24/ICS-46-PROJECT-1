#ifndef SMARTSOLVER_HPP
#define SMARTSOLVER_HPP

#include <ics46/factory/DynamicFactory.hpp>
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include <vector>
#include <random>
#include "Maze.hpp"
#include "Direction.hpp"
using namespace std;

class SmartSolver :public MazeSolver
{
public:
    SmartSolver();
    virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
    bool nextMove(const Maze & maze ,int currentX, int currentY, vector<vector<bool>>& mazeStatus,pair<int,int> endPoint,MazeSolution& mazeSolution);
    vector<Direction> getAdjacentDirections(const Maze & maze ,int currentX, int currentY,vector<vector<bool>>& mazeStatus);
    int getRandomDirection(vector<Direction> availableDirections);

};

#endif 
