#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
  PNG* image = new PNG(w, h);
  return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double hue) {
  HSLAPixel *p = new HSLAPixel(hue, 0.8, 0.5);
  return p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original= new PNG();
cout << "Reached line 23" << endl;
    original->readFromFile(inputFile);
    cout << "Reached line 25" << endl;
    unsigned int width = original->width();
    cout << width << endl;
    unsigned int height = original->height();
cout << height << endl;
    // Create out.png
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(360);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
   for (unsigned int y = 1; y< height; y++) {
        for (unsigned int x = 1; x < width; x++) {
            // Calculate the pixel difference

            HSLAPixel& prev = original->getPixel(x - 1, y - 1);

            HSLAPixel& curr = original->getPixel(x, y);

            double diff = std::fabs(curr.h - prev.h);


            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel &currOutPixel=(*output).getPixel(x, y);

            if (diff > 20) {
                currOutPixel = *myPixel;

            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
