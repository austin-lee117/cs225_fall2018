#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"
#include <vector>
using namespace cs225;
using namespace std;


/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  picture = png;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  trav.push_back(&traversal);
  pick.push_back(&colorPicker);

}

Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  animation.addFrame(picture);
  ImageTraversal* it;
  ColorPicker* cp;
   auto itcurr = trav.begin();
   cout<<typeid(itcurr).name()<<endl;
  auto cpcurr = pick.begin();
  unsigned frames;
  while(itcurr!=trav.end()){
    it = *itcurr;
    cp = *cpcurr;
    frames = 0;
    for(ImageTraversal::Iterator asdf = it->begin();asdf!=it->end();++asdf){
      Point a = *asdf;
      HSLAPixel &pix = picture.getPixel(a.x, a.y);
      const HSLAPixel &col = cp->getColor(a.x, a.y);
      pix = col;
      frames +=1;
      if(frames==frameInterval){
        animation.addFrame(picture);
        frames = 0;
      }
    }
    ++itcurr;
    ++cpcurr;
  }
  animation.addFrame(picture);
  return animation;
}
