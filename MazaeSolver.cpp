#include "myMazeSolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "Direction.hpp"
#include <iostream>
#include <random>
#include <vector>
using namespace std;
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MySolver, "MySolver (Required)");



void recursive(vector<vector<bool>>& MarkVector, const Maze& maze, MazeSolution& mazesolution, vector<std::string> movevector){
	vector<std::string> moveVector = movevector;
	int lastIndex = moveVector.size();
	int x = (mazesolution.getCurrentCell()).first;
	int y = (mazesolution.getCurrentCell()).second;
	int width = maze.getWidth();
	int height = maze.getHeight();
	MarkVector[x][y] = true;
	if(!maze.wallExists(x,y, Direction::up) && MarkVector[x][y-1] != true && y-1>=0){
		moveVector.push_back("up");
	}
	else if (!maze.wallExists(x,y, Direction::down) && MarkVector[x][y+1] != true && y+1<=height-1){
		moveVector.push_back("down");
	}
	else if (!maze.wallExists(x,y, Direction::left) && MarkVector[x-1][y] != true && x-1>=0){
		moveVector.push_back("left");
	}
	else if (!maze.wallExists(x,y, Direction::right) && MarkVector[x+1][y] != true && x+1<=width-1){
		moveVector.push_back("right");
	}
	else{
		moveVector.push_back("None");
	}
	while(!mazesolution.isComplete()){
		if(moveVector.at(lastIndex) == "up"){
			mazesolution.extend(Direction::up);
			recursive(MarkVector, maze, mazesolution, moveVector);
		}
		else if(moveVector.at(lastIndex) == "down"){
			mazesolution.extend(Direction::down);
			recursive(MarkVector, maze, mazesolution, moveVector);
		}
		else if(moveVector.at(lastIndex) == "left"){
			mazesolution.extend(Direction::left);
			recursive(MarkVector, maze, mazesolution, moveVector);
		}
		else if(moveVector.at(lastIndex) == "right"){
			mazesolution.extend(Direction::right);
			recursive(MarkVector, maze, mazesolution, moveVector);
		}
		else if (moveVector.at(lastIndex) == "None"){
			mazesolution.backUp();
			moveVector.erase(moveVector.begin()+lastIndex);
			recursive(MarkVector, maze, mazesolution, moveVector);
		}
	}
	return;
}




void MySolver::solveMaze(const Maze& maze, MazeSolution& mazesolution){
	vector<vector<bool>> MarkVector(maze.getWidth(), vector<bool>(maze.getHeight(), false));
	vector<std::string> movevector;
	recursive(MarkVector, maze, mazesolution, movevector);
}
