#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG png;

  png.readFromFile(inputFile);
  PNG png2(png.width(),png.height());

  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel_in = png.getPixel(x, y);
      HSLAPixel & pixel_out = png2.getPixel(png2.width()-x-1, png2.height()-y-1);
      pixel_out = pixel_in;

}
}
png2.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  double hue = 23;
  // TODO: Part 3
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      if (y< (png.height()/10)) {

        pixel.h = hue;
        pixel.l = 0.5;
        pixel.s = 0.8;
      }
      else {

      if (hue == 360) {
        hue = 0;
      } else {
        hue++;
      }
      pixel.h = hue;
      pixel.l = 0.5;
      pixel.s = 0.8; }


    }
  }

  return png;
}
