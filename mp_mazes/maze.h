/* Your code here! */

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace std;
using namespace cs225;

class SquareMaze {

public:
  //No-parameter constructor.
  SquareMaze ();

  //Makes a new SquareMaze of the given height and width.
  void 	makeMaze (int width, int height);

  //This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
  bool 	canTravel (int x, int y, int dir) const;

  //Sets whether or not the specified wall exists.
  void 	setWall (int x, int y, int dir, bool exists);

  //Solves this SquareMaze.
  std::vector<int> solveMaze();

  //Draws the maze without the solution.
  cs225::PNG* drawMaze() const;

  //This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.
  cs225::PNG* drawMazeWithSolution();

  PNG* drawCreativeMaze() const;

private:

  vector<pair<bool, bool>> walls;
  DisjointSets dsets;
  int _width;
  int _height;


};
