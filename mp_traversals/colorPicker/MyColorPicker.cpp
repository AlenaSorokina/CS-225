#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cmath>
using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(HSLAPixel color1, HSLAPixel color2, Point center){
  color1_ = color1;
  color2_ = color2;
  center_ = center;
 }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  double dx = x - center_.x;
  double dy = y - center_.y;
  double d = sqrt((dx * dx) + (dy * dy));
  double pct = d / 10;

  if (pct >= 1) {
    return color2_;
  }

  double h = color1_.h + pct*0.05;
  if (h >= 360) { h -= 360; }


  return HSLAPixel(h, 1, 0.5);
}
