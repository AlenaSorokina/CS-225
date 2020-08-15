/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"

class Image:public cs225::PNG {

public:
  void darken();
  void darken(double amount);
  void desaturate();
  void desaturate(double amount);
  void grayscale();
  void illinify();
  void lighten();
  void lighten(double amount);
  void rotateColor(double degrees);
  void saturate();
  void saturate(double amount);
  void scale(double factor);
  void scale(unsigned w, unsigned h);

};
