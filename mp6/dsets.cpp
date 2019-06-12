/* Your code here! */
#include "dsets.h"
void DisjointSets::addelements(int num){
  for (int i =0; i<num; i++){
    vect.push_back(-1);
  }
}
int DisjointSets::find(int elem){
  if(vect[elem]<0){
    return elem;
  }
  return find(vect[elem]);

}
void DisjointSets::setunion(int a, int b){
  int x = find(a);
  int y = find(b);
  int s1 = size(x);
  int s2 = size(y);
  int resized = s1+s2;
  if(s1<s2){
    vect[x] = y;
    vect[y] = resized*-1;
  }
  else{
    vect[y] = x;
    vect[x] = resized*-1;
  }

}
int DisjointSets::size(int elem){
  int ret = find(elem);
  return vect[ret]*-1;
}
