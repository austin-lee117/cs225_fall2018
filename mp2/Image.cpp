#include "Image.h"
#include <cmath>
using namespace cs225;
Image::Image():PNG(){}
Image::Image(const Image &pic):PNG(pic){

}

void Image::lighten() {
  for (unsigned int i=0; i<width() ;i++){
    for (unsigned int j=0; j<height(); j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.l+=0.1;
      if(pixel.l>1.0){
        pixel.l = 1.0;
      }
    }
  }
}
void Image::lighten(double amount){
  for (unsigned int i=0; i<width(); i++){
    for (unsigned int j=0; j<height();j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.l+=amount;
      if(pixel.l>1.0){
        pixel.l = 1.0;
      }
    }
  }
}
void Image::darken() {
  for (unsigned int i=0; i<width() ;i++){
    for (unsigned int j=0; j<height(); j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.l-=0.1;
      if(pixel.l<0.0){
        pixel.l = 0.0;
      }
    }
  }
}
void Image::darken(double amount){
  for (unsigned int i=0; i<width(); i++){
    for (unsigned int j=0; j<height();j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.l-=amount;
      if(pixel.l<0.0){
        pixel.l = 0.0;
      }
    }
  }
}
void Image::saturate() {
  for (unsigned int i=0; i<width() ;i++){
    for (unsigned int j=0; j<height(); j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.s+=0.1;
      if(pixel.s>1.0){
        pixel.s = 1.0;
      }
    }
  }
}
void Image::saturate(double amount){
  for (unsigned int i=0; i<width(); i++){
    for (unsigned int j=0; j<height();j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.s+=amount;
      if(pixel.s>1.0){
        pixel.s = 1.0;
      }
    }
  }
}
void Image::desaturate() {
  for (unsigned int i=0; i<width() ;i++){
    for (unsigned int j=0; j<height(); j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.s-=0.1;
      if(pixel.s<0.0){
        pixel.s = 0.0;
      }
    }
  }
}
void Image::desaturate(double amount){
  for (unsigned int i=0; i<width(); i++){
    for (unsigned int j=0; j<height();j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.s-=amount;
      if(pixel.s<0.0){
        pixel.s = 0.0;
      }
    }
  }
}
void Image::grayscale(){
  for (unsigned int i=0; i<width(); i++){
    for (unsigned int j=0; j<height();j++){
      HSLAPixel &pixel = getPixel(i, j);
      pixel.s-=0;
      }
    }
  }

void Image::illinify() {

  for(unsigned x =0;x<width();x++){
    for(unsigned y = 0;y<height();y++){
      HSLAPixel &pixel = getPixel(x,y);
      double hue = pixel.h;
      if ((hue>113.5)&&(hue<293.5)){
        pixel.h = 216;
      }
      else pixel.h=11;

    }
  }
}
void Image::rotateColor (double degrees){
  for(unsigned x =0;x<width();x++){
    for(unsigned y = 0;y<height();y++){
      HSLAPixel &pixel = getPixel(x,y);
      pixel.h += degrees;
      if (pixel.h>360.0){
        pixel.h = pixel.h-360.0;
      }
      if (pixel.h<0.0){
        pixel.h = pixel.h +360.0;
      }
}}}

void Image::scale(double factor){
if (factor == 1.0){
  return;
}
  Image original(*this);
  resize(factor*width(),factor*height());
  for (unsigned int i=0; i<width(); i++){
    for (unsigned int j=0; j<height(); j++){
      HSLAPixel&pixel = original.getPixel(i/factor, j/factor);
      HSLAPixel&change = getPixel(i,j);
      change = pixel;
    }
  }
  return;
}

void Image::scale (unsigned w, unsigned h){
  double factor = w/width();
  scale(factor);

}
