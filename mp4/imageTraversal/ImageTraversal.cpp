#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  position = NULL;

}
ImageTraversal::Iterator::Iterator(ImageTraversal *pnter){
  position = pnter;
  position->visited[position->pnt.x][position->pnt.y]=1;
}

ImageTraversal::ImageTraversal(const PNG& png, const Point& start, double tolerance):pnt(start), pic(png){
  pwidth = pic.width();
  pheight = pic.height();
  tol = tolerance;
  visited = new int*[pwidth];
  for (unsigned i = 0; i<pwidth; i++){
    visited[i] = new int[pheight];
  }
  for (unsigned i = 0; i<pwidth; i++){
    for (unsigned j = 0; j<pheight; j++){
      visited[i][j] = 0;
    }
  }
  visited[pnt.x][pnt.y] = 1;
}


bool ImageTraversal::helper(Point check){

      HSLAPixel& pix1 = (pic.getPixel(check.x, check.y));
      HSLAPixel& pix2 = (pic.getPixel(pnt.x, pnt.y));
        if(calculateDelta(pix1, pix2)<tol)
        return true;

return false;

}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //returns previous Point, not incremented one.
  Point base = position->pop();
  Point p1 = Point(base.x+1, base.y);
  Point p2 = Point(base.x, base.y+1);
  Point p3 = Point(base.x-1, base.y);
  Point p4 = Point(base.x, base.y-1);

  if(base.x<position->pwidth-1){
  if(position->visited[base.x+1][base.y] == 0){
    if(position->helper(p1)){
      position->add(p1);
    }
  }}
  if(base.y<position->pheight-1){
  if(position->visited[base.x][base.y+1] == 0){
    if(position->helper(p2)){
      position->add(p2);
    }
  }}
  if(base.x>0){
  if(position->visited[base.x-1][base.y] == 0){
    if(position->helper(p3)){
      position->add(p3);
    }
  }}
  if(base.y>0){
  if(position->visited[base.x][base.y-1] == 0){
    if(position->helper(p4)){
      position->add(p4);
    }
  }}

while(1){
  if(position->empty()){
    position= NULL;
    break;
  }
  Point temp = position -> peek();
  if(position->visited[temp.x][temp.y]==1){
    position -> pop();
    continue;
  }
  position -> visited[temp.x][temp.y] = 1;
  break;
}

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  if(position!=NULL)
  return position->peek();
  else return Point();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(this->position == other.position)
  return false;
  else return true;
}

ImageTraversal::~ImageTraversal(){
  for (unsigned i = 0; i<pwidth; i++){
    delete visited[i];
  }
  delete visited;
}
