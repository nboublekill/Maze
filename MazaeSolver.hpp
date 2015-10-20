#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP
#include "MazeSolver.hpp"
class MySolver : public MazeSolver{
public:
	MySolver(){};
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
};
#endif // MYMAZESOLVER_HPP
