/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel() {
    h = 1;
    s = 1;
    l = 1;
    a = 1;
}

  HSLAPixel::HSLAPixel(double a_,double b_,double c_) {
    this->h = a_;
    this->s = b_;
    this->l = c_;
    a=1;
  }

  HSLAPixel::HSLAPixel(double a_,double b_,double c_, double d_) {
    this->h = a_;
    this->s = b_;
    this->l = c_;
    this->a = d_;
  }

}
