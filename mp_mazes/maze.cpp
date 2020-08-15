#include <cstdlib>
#include "maze.h"
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


SquareMaze::SquareMaze() {
	_width = 0;
	_height = 0;
}

/*Makes a new SquareMaze of the given height and width using
a randomized version of Kruskal's algorithm.

1. Create a list of all walls, and create a set for each cell,
each containing just that one cell.
2. For each wall, in some random order:
  If the cells divided by this wall belong to distinct sets:
    1. Remove the current wall.
    2. Join the sets of the formerly divided cells.*/

void 	SquareMaze::makeMaze (int width, int height){
  _width = width;
  _height = height;
  int size = _width*_height;

  dsets.addelements(size);
  for(int i = 0; i<size; i++) {
    walls.push_back(pair<bool, bool> (true, true)); }

  int j = 0;

  while(j<size-1) {
    int X_coord = rand() %_width;
    int Y_coord = rand() %_height;
    bool wall = rand() % 2;

    if(wall) {
      if(walls[X_coord + Y_coord*_width].first && (X_coord<_width-1) && (dsets.find(X_coord + Y_coord*_width) !=  dsets.find(X_coord + Y_coord*_width+1))) {
        walls[X_coord + Y_coord*_width].first = false;
        dsets.setunion(dsets.find(X_coord + Y_coord*_width),dsets.find(X_coord + Y_coord*_width+1));
        j++;
      }
    } else {
      if(walls[X_coord + Y_coord*_width].second && (Y_coord<_height-1) && (dsets.find(X_coord + Y_coord*_width) !=  dsets.find(X_coord + (Y_coord+1)*_width))) {
        walls[X_coord + Y_coord*_width].second = false;
        dsets.setunion(dsets.find(X_coord + Y_coord*_width),dsets.find(X_coord + (Y_coord+1)*_width));
        j++;
      }

    }
  }
}





//This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
bool 	SquareMaze::canTravel (int x, int y, int dir) const {
  if(dir == 0) {
    if(x>=_width-1) return false;
    return !walls[x+y*_width].first;
  }
  if(dir == 1) {
    if(y>= _height -1) return false;
    return !walls[x+y*_width].second;
  }

  if(dir == 2) {
    if(x<1) return false;
    return !walls[x-1+y*_width].first;
  }

  if(dir==3) {
    if(y<1) return false;
    return !walls[x+(y-1)*_width].second;
  }

  return false;
}

//Sets whether or not the specified wall exists.
void 	SquareMaze::setWall (int x, int y, int dir, bool exists) {
  if(dir == 0) {
    walls[x+y*_width].first = exists;
  }
  if(dir == 1) {
    walls[x+y*_width].second = exists;
  }
}

//Solves this SquareMaze.
std::vector<int> SquareMaze::solveMaze(){
  vector<int> path;

  std::vector<int> bottom;
  map<int, int> iter;
  vector<bool> visited;

  for(int i =0; i<_width*_height; i++){
    visited.push_back(false);
  }
  queue<int> traversal;
  traversal.push(0);
  visited[0] = true;

  while(!traversal.empty()) {
    int node = traversal.front();
    traversal.pop();
    int x = node%_width;
    int y = node/_width;
    if(y == _height -1) bottom.push_back(node);

    if(canTravel(x,y, 0) && visited[node+1]== false) {
      iter.insert(pair<int, int>(node+1, node));
      visited[node+1]= true;
      traversal.push(node+1);
    }

    if(canTravel(x,y, 1) && visited[node+_width]== false) {
      iter.insert(pair<int, int>(node+_width, node));
      visited[node+_width]= true;
      traversal.push(node+_width);
    }

    if(canTravel(x,y, 2) && visited[node-1]== false) {
      iter.insert(pair<int, int>(node-1, node));
      visited[node-1]= true;
      traversal.push(node-1);
    }

    if(canTravel(x,y, 3) && visited[node-_width]== false) {
      iter.insert(pair<int, int>(node-_width, node));
      visited[node-_width]= true;
      traversal.push(node-_width);
    }

  }

  stack<int> stack;
  int last = _width-1;
  while(bottom[last] == bottom[last-1]) {
    last=-1;
  }
  int begin = bottom[last];
  while(begin !=0) {
    int prev = iter[begin];
    if(begin == prev+1) stack.push(0);
    else if(begin == prev + _width) stack.push(1);
    else if(begin == prev-1) stack.push(2);
    else if(begin == prev - _width) stack.push(3);
    begin = prev;
  }

  int size= stack.size();
  for(int i=0; i<size; i++ ) {
    path.push_back(stack.top());
    stack.pop();
  }
  return path;

}

//Draws the maze without the solution.
PNG* SquareMaze::drawMaze() const{
  PNG* image = new PNG(_width*10+1,_height*10+1);
  for(int i =0; i<_width; i++){
    for(int j =0; j<_height; j++){
      if(j==0) {
        for(unsigned k=0; k<10; k++){
          if((i*10+k<1)||(i*10+k>9)){
            HSLAPixel & cur_pixel = image->getPixel(i*10+k, 0);
            cur_pixel.l = 0;
          }
        }
      }
      if(i==0) {
        for(unsigned k=0; k<10;k++){
          HSLAPixel & cur_pixel = image->getPixel(0, j*10+k);
          cur_pixel.l = 0;
        }
      }
      if(!canTravel(i,j,0)) {
        for(unsigned k=0; k<=10;k++){
          HSLAPixel & cur_pixel = image->getPixel((i+1)*10, j*10+k);
          cur_pixel.l = 0;
        }
      }
      if(!canTravel(i,j,1)) {
        for(unsigned k=0; k<=10;k++){
          HSLAPixel & cur_pixel = image->getPixel(i*10+k, (j+1)*10);
          cur_pixel.l = 0;
        }
      }
    }
  }
  return image;

}

//This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.
PNG* SquareMaze::drawMazeWithSolution(){
  PNG* image = drawMaze();
  std::vector<int> path = solveMaze();
  int x = 5;
  int y = 5;

  for(unsigned i=0; i<path.size(); i++){
    if(path[i] == 0){
      for(int i =0; i<10; i++){
        HSLAPixel & cur_pixel = image->getPixel(x,y);
        cur_pixel.l = 0.5;
        cur_pixel.h = 0;
        cur_pixel.s =1;
        x++;
      }
    }
    if(path[i] == 1){
      for(int i =0; i<10; i++){
        HSLAPixel & cur_pixel = image->getPixel(x,y);
        cur_pixel.l = 0.5;
        cur_pixel.h = 0;
        cur_pixel.s =1;
        y++;
      }
    }
    if(path[i] == 2){
      for(int i =0; i<10; i++){
        HSLAPixel & cur_pixel = image->getPixel(x,y);
        cur_pixel.l = 0.5;
        cur_pixel.h = 0;
        cur_pixel.s =1;
        x--;
      }
    }
    if(path[i] == 3){
      for(int i =0; i<10; i++){
        HSLAPixel & cur_pixel = image->getPixel(x,y);
        cur_pixel.l = 0.5;
        cur_pixel.h = 0;
        cur_pixel.s =1;
        y--;
      }
    }
  }
    HSLAPixel & k = image->getPixel(x,y);
    k.l = 0.5;
    k.h = 0;
    k.s =1;
    k.a = 1;
    x-=4;
    y+=5;

    for(int i =0; i<9; i++){
      HSLAPixel & cur_pixel = image->getPixel(x,y);
      cur_pixel.l = 1;
      cur_pixel.a =1;
      x++;
    }
    return image;

  }

	//Draws creative maze
	PNG* SquareMaze::drawCreativeMaze() const{
	  PNG* image = new PNG(_width*10+1,_height*10+1);
	  for(int i =0; i<_width; i++){
	    for(int j =0; j<_height; j++){
	      if(j==0) {
	        for(unsigned k=0; k<10; k++){
	          if((i*10+k<1)||(i*10+k>9)){
	            HSLAPixel & cur_pixel = image->getPixel(i*10+k, 0);
	            cur_pixel.l = 0.5;
							cur_pixel.h = rand() % 360;
							cur_pixel.s = 1;
	          }
	        }
	      }
	      if(i==0) {
	        for(unsigned k=0; k<10;k++){
	          HSLAPixel & cur_pixel = image->getPixel(0, j*10+k);
	          cur_pixel.l = 0.5;
						cur_pixel.h = rand() % 360;
						cur_pixel.s = 1;
	        }
	      }
	      if(!canTravel(i,j,0)) {
	        for(unsigned k=0; k<=10;k++){
	          HSLAPixel & cur_pixel = image->getPixel((i+1)*10, j*10+k);
	          cur_pixel.l = 0.5;
						cur_pixel.h = rand() % 360;
						cur_pixel.s = 1;
	        }
	      }
	      if(!canTravel(i,j,1)) {
	        for(unsigned k=0; k<=10;k++){
	          HSLAPixel & cur_pixel = image->getPixel(i*10+k, (j+1)*10);
	          cur_pixel.l = 0.5;
						cur_pixel.h = rand() % 360;
						cur_pixel.s = 1;
	        }
	      }
	    }
	  }
	  return image;

	}
