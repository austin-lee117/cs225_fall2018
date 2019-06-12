#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
  PNG* original= new PNG();
  original->readFromFile(inputFile);
  unsigned int width = original->width();
  unsigned int height = original->height();
  PNG* output = new PNG(width, height);
  for (unsigned int x = 0; x<width;x++){
    for (unsigned int y = 0; y<height; y++){
      HSLAPixel &aye = original->getPixel(width-x-1,height-y-1);
      HSLAPixel &nay = output->getPixel(x,y);
      nay = aye;


    }
  }
  output->writeToFile(outputFile);
  delete original;
  delete output;
}



PNG myArt(unsigned int width, unsigned int height) {

  PNG png = PNG(width, height);
  HSLAPixel *ocean = new HSLAPixel (213, 1, 0.5);

  for (unsigned int x = 0; x<width; x++){
    for (unsigned int y = 0; y<height; y++){
      HSLAPixel *sky = new HSLAPixel(53-(sqrt((x-width/2)*(x-width/2)+(y-height/2)*(y-height/2)))/6,1,0.5);
      HSLAPixel &out = png.getPixel(x,y);
      out = *sky;
    }
  }

  for (unsigned int x = 0; x<width; x++){
    for (unsigned int y = (height*0.6875); y<height; y++){
      HSLAPixel &out = png.getPixel(x,y);
      out = *ocean;
    }
  }

  return png;
}
