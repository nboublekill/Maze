#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP
#include "MazeGenerator.hpp"
class MyGenerator : public MazeGenerator{
public:
	MyGenerator(){};
	virtual void generateMaze(Maze& maze);
};
#endif // MYMAZEGENERATOR_HPP
