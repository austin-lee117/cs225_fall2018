#include "Image.h"
#include "StickerSheet.h"

int main() {
Image fortnite;
fortnite.readFromFile("basepic.png");
Image pic1;
pic1.readFromFile("image1.png");
Image pic2;
pic2.readFromFile("image2.png");
Image pic3;
pic3.readFromFile("image3.png");
StickerSheet * vijay = new StickerSheet(fortnite, 3);
vijay->addSticker(pic1, 300, 800);
vijay->addSticker(pic2, 1000, 200);
vijay->addSticker(pic3, 3000, 1500);
Image output = vijay->render();

output.writeToFile("myImage.png");




  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
