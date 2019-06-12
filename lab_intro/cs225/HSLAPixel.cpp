/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel(){
    a = 1.0;
    l = 1.0;
    s = 0.0;
    h = 0.0;
  }
  HSLAPixel::HSLAPixel(double hue, double sat, double lum, double alpha){
    a = alpha;
    h = hue;
    s = sat;
    l = lum;
  }
  HSLAPixel::HSLAPixel(double hue, double sat, double lum){
    h = hue;
    s = sat;
    l = lum;
    a = 1.0;
  }
}
