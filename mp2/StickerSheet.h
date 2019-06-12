/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <string>
#include <iostream>
using namespace std;

class StickerSheet : public Image{
public:
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  const StickerSheet& operator = (const StickerSheet&other);
  void changeMaxStickers(unsigned max);
  int addSticker (Image &sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image * getSticker (unsigned index) const;
  Image render() const;
  void copy(const StickerSheet &other);
  void kill();

private:
  Image** arr;
  unsigned * xes;
  unsigned * yes;
  unsigned max_;

  Image *basePic;

};
