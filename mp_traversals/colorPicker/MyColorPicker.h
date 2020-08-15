#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(HSLAPixel color1, HSLAPixel color2, Point center);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel color1_;
  HSLAPixel color2_;
  Point center_;

};
