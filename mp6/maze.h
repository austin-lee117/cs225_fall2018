/* Your code here! */
#pragma once
#include<iostream>
#include<math.h>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>


#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
using namespace cs225;

class SquareMaze{
public:
SquareMaze();
void makeMaze(int width, int height);
bool canTravel(int x, int y, int dir) const;
void setWall(int x, int y, int dir, bool exists);
vector<int> solveMaze();
PNG * drawMaze() const;
PNG * drawMazeWithSolution();
vector<int>Down;
vector<int>Right;
private:
int width_;
int height_;
int size_;



};
