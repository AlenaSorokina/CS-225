#include "Image.h"
using cs225::HSLAPixel;

void Image::darken() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if (pixel.l > 0.1) {
        pixel.l = pixel.l-0.1;
      } else {
        pixel.l = 0;
      }
    }
  }

}
void Image::darken(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if ((pixel.l-amount) > 0) {
        pixel.l = pixel.l-amount;
      } else {
        pixel.l = 0;
      }
    }
  }

}
void Image::desaturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if (pixel.s > 0.1) {
        pixel.s = pixel.s-0.1;
      } else {
        pixel.s = 0;
      }
    }
  }

}
void Image::desaturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if ((pixel.s-amount) > 0) {
        pixel.s = pixel.s-amount;
      } else {
        pixel.s = 0;
      }
    }
  }

}
void Image::grayscale(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      pixel.s = 0;
    }
  }


}
void Image::illinify(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if ((pixel.h>114) && (pixel.h < 294)) {
        pixel.h = 216;
      }
      else {
        pixel.h = 11;
      }
    }
  }

}

void Image::lighten(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if (pixel.l < 0.9) {
        pixel.l +=0.1;
      } else {
        pixel.l =1;
      }

}
}
}
void Image::lighten(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if ((pixel.l+amount)<1) {
        pixel.l +=amount;
      } else {
        pixel.l =1;
      }
    }
  }

}
void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      pixel.h +=degrees;

      if (pixel.h>360) {
        pixel.h = pixel.h-360;
      } else if (pixel.h<0) {
        pixel.h = pixel.h+360;
      }

    }
  }


}
void Image::saturate(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if (pixel.s < 0.9) {
        pixel.s +=0.1;
      } else {
        pixel.s =1;
      }
    }
  }

}
void Image::saturate(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if ((pixel.s+amount)<1) {
        pixel.s +=amount;
      } else {
        pixel.s =1;
      }
    }
  }

}
void Image::scale(double factor){
  unsigned int new_width = (unsigned int) (factor*this->width());
  unsigned int new_height = (unsigned int) (factor*this->height());

  PNG oldImage(*this);
  this->resize(new_width, new_height);

  for (unsigned x = 0; x < new_width; x++) {
    for (unsigned y = 0; y < new_height; y++) {
      unsigned oldX = (unsigned) ((float)x / factor);
      unsigned oldY = (unsigned) ((float)y / factor);

      HSLAPixel & newPixel = this->getPixel(x, y);
      HSLAPixel & oldPixel = oldImage.getPixel(oldX, oldY);
      newPixel = oldPixel;

    }
  }


}
void Image::scale(unsigned w, unsigned h){
  unsigned factor_w = (double) (w/this->width());
  unsigned factor_h = (double) (h/this->height());
  if (factor_w> factor_h) {
    scale(factor_h);
  } else {
    scale(factor_w);
  }

}
