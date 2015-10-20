#include "myMazeGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>
#include <iostream> 
#include <vector>
using namespace std;
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyGenerator, "MyGenerator(Required)");

vector<std::string> validmove(vector<vector<bool>>& MarkVector, int x, int y, Maze& maze){
	int width = maze.getWidth();
	int height = maze.getHeight();
	vector<std::string> moveVector;
	if (y-1>=0 && MarkVector[x][y-1] != true){
		moveVector.push_back("up");
	}
	if (y+1<= height-1 && MarkVector[x][y+1] != true){
		moveVector.push_back("down");
	}
	if (x-1>=0 && MarkVector[x-1][y] != true){
		moveVector.push_back("left");
	}
	if (x+1<= width-1 && MarkVector[x+1][y] != true){
		moveVector.push_back("right");
	}
	return moveVector;

}




void Recursive(vector<vector<bool>>& MarkVector, int x, int y, Maze& maze){
	MarkVector[x][y] = true;
	vector<std::string>moveVector = validmove(MarkVector,x,y,maze);

	default_random_engine engine{random_device{}()};
	while(moveVector.size()!=0){
		int numberOfValidMove = moveVector.size();
		uniform_int_distribution<int> distribution{0, numberOfValidMove-1};
		int index = distribution(engine);
		if(moveVector.at(index) == "up"){
			if(maze.wallExists(x,y, Direction::up)){
				maze.removeWall(x,y, Direction::up);
				y = y-1;
				Recursive(MarkVector, x, y, maze);
				moveVector = validmove(MarkVector,x,y,maze);
			}
		}

		else if (moveVector.at(index) == "down"){
			if(maze.wallExists(x,y, Direction::down)){
				maze.removeWall(x,y, Direction::down);
				y = y+1;
				Recursive(MarkVector, x, y, maze);
				moveVector = validmove(MarkVector,x,y,maze);
			}
		}

		else if(moveVector.at(index) == "left"){
			if(maze.wallExists(x,y, Direction::left)){
				maze.removeWall(x,y, Direction::left);
				x= x-1;
				Recursive(MarkVector, x, y, maze);
				moveVector = validmove(MarkVector,x,y,maze);
			}
		}

		else if (moveVector.at(index) == "right"){
			if(maze.wallExists(x,y, Direction::right)){
				maze.removeWall(x,y, Direction::right);
				x = x+1;
				Recursive(MarkVector, x, y, maze);
				moveVector = validmove(MarkVector,x,y,maze);
			}
		}
	}
	return;
	
}

void MyGenerator::generateMaze(Maze& maze){
	vector<vector<bool>> MarkVector(maze.getWidth(), vector<bool>(maze.getHeight(), false));
	maze.addAllWalls();
	Recursive(MarkVector,0,0, maze);
}
