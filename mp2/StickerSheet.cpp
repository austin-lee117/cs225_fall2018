#include "StickerSheet.h"
#include <string>
#include <iostream>
using namespace std;
#include "Image.h"
#include "cs225/PNG.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max){
  arr = new Image*[max];
  basePic = new Image(picture);
  max_ = max;
  xes = new unsigned[max];
  yes = new unsigned[max];
  for (unsigned i = 0; i <max_;i++){
    arr[i] = NULL;
    xes[i]=0;
    yes[i]=0;
  }


}
StickerSheet::~StickerSheet(){

    kill();
  }


StickerSheet::StickerSheet(const StickerSheet &other){
//  unsigned int k = sizeof(other.arr)/sizeof(other.arr[0]);
copy(other);

}
void StickerSheet::kill(){
  if(arr!=NULL){
  for (unsigned i=0; i<max_;i++){
        delete arr[i];
    arr[i] = NULL;
  }
}
//    delete[] arr;
  delete[] arr;
  arr = NULL;
  delete[] xes;
  xes = NULL;
  delete[] yes;
  yes = NULL;


}
void StickerSheet::copy(const StickerSheet &other){
  basePic = new Image(*other.basePic);
  max_ = other.max_;

 xes = new unsigned[max_];
 yes = new unsigned[max_];
   arr = new Image*[max_];


  for (unsigned int i =0; i<max_;i++){
    if(other.arr[i]!=NULL){
    arr[i] = new Image(*other.arr[i]);
    xes[i] = other.xes[i];
    yes[i] = other.yes[i];
  }
  else arr[i] = NULL;
}
}
const StickerSheet& StickerSheet::operator = (const StickerSheet&other){
  if(this!=&other){
  kill();
//  unsigned int k = sizeof(other.arr)/sizeof(other.arr[0]);
  copy(other);
}
return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
  if(max==max_) {return;}
  Image ** temp = new Image*[max];
  //unsigned int k = sizeof(this->arr)/sizeof(this->arr[0]);
  unsigned * tempx = new unsigned[max];
  unsigned * tempy = new unsigned[max];
  if (max>max_){
    for (unsigned int i =0; i< max_; i++){
    temp[i] = arr[i];
    tempx[i] = xes[i];
    tempy[i] = yes[i];
  }
    for (unsigned int i = max_; i<max; i++){
      temp[i] = NULL;
      tempx[i] = 0;
      tempy[i] = 0;
    }
max_=max;
}
  else{

    for (unsigned int i = 0; i<max; i++){
      temp[i] = arr[i];
      tempx[i] = xes[i];
      tempy[i] = yes[i];
        }
    for (unsigned i = max; i<max_;i++){
      delete arr[i];
    }
  }
    delete[] arr;
    arr = temp;
    xes = tempx;
    yes = tempy;
    max_=max;

  }



int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
//  int k = 0;
//  int max = sizeof(this->arr)/sizeof(this->arr[0]);

  for (unsigned i = 0; i<max_; i++){
    if (arr[i] == NULL){
      arr[i] = new Image(sticker);

      xes[i] = x;

      yes[i] = y;
      return i;
    }
  }
  return -1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if (index>max_-1)
    return false;
  if (arr[index]==NULL)
      return false;
  xes[index] = x;
  yes[index] = y;
  return true;
}
void StickerSheet::removeSticker(unsigned index){
  if (index>max_-1)
    return;
  if (arr[index] == NULL)
    return;

  delete arr[index];
  arr[index]=NULL;
  xes[index] = 0;
  yes[index] = 0;
  //numStickers--;
  return;

}
Image * StickerSheet::getSticker (unsigned index) const{

  if (index>max_-1){
    return NULL;
  }

  if (arr[index] ==NULL){
    return NULL;
}
  return arr[index];

}
Image StickerSheet::render() const{

    unsigned int totalW = basePic->width();
    unsigned int totalH = basePic->height();
    for (unsigned int i=0; i<max_;i++){
      if(arr[i] != NULL){
      unsigned w = xes[i] + arr[i]->width();
      unsigned h = yes[i] + arr[i]->height();

      if (w>totalW) totalW=w;
      if (h>totalH) totalH=h;
    }
  }

    Image *out = new Image(*basePic);
    out->resize(totalW, totalH);
    for (unsigned int i =0; i<max_;i++){
      if(arr[i]!=NULL){
      for(unsigned int a = xes[i]; a<xes[i]+arr[i]->width();a++){
        for(unsigned int b = yes[i]; b<yes[i]+arr[i]->height();b++){
          HSLAPixel & pic = out->getPixel(a,b);
          HSLAPixel & sticker = arr[i]->getPixel(a-xes[i],b-yes[i]);
          if (sticker.a!=0){
            pic=sticker;
          }
        }
      }
    }
}
    Image output = *out;
    delete out;
    return output;
}
