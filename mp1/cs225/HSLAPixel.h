/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#ifndef CS225_HSLAPIXEL_H_
#define CS225_HSLAPIXEL_H_

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel{
  public:
    double h;
    double l;
    double a;
    double s;
    HSLAPixel();
    HSLAPixel(double hue, double sat, double lum, double alpha);
    HSLAPixel(double hue, double sat, double lum);
  };
  }

#endif
