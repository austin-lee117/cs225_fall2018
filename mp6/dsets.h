/* Your code here! */
#pragma once
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

class DisjointSets{
public:
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
  int size(int elem);

  vector<int> vect;
};
