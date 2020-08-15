#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  finished_ = true;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start,  PNG png, double tolerance) {
  traversal_ = traversal;
  start_ = start;
  current_ = traversal_->peek();
  png_ = png;
  tolerance_ = tolerance;
  finished_ = false;
  /** @todo [Part 1] */
}

bool ImageTraversal::Iterator::check(Point o) {
  if((o.x < png_.width()) && (o.y < png_.height())) {
    return true;
  }
  return false;

}

/**ImageTraversal::Iterator::~Iterator(){
  if(traversal_ !=NULL) {
    delete traversal_;
  }
  traversal_ = NULL;
}
*/


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point top = traversal_->pop();
  traversal_->setVisited(top);

  Point right(top.x+1, top.y);
  Point below(top.x, top.y+1);
  Point left(top.x-1, top.y);
  Point above(top.x, top.y-1);

  HSLAPixel & p1 = png_.getPixel(start_.x, start_.y);

  if(check(right)){
    HSLAPixel & p2 = png_.getPixel(right.x, right.y);
    double delta = calculateDelta(p1, p2);
    if (delta < tolerance_) {
      traversal_->add(right);
    }
  }

  if(check(below)){
    HSLAPixel & p2 = png_.getPixel(below.x, below.y);
    double delta = calculateDelta(p1, p2);
    if (delta < tolerance_) {
      traversal_->add(below);
    }
  }

  if(check(left)){
    HSLAPixel & p2 = png_.getPixel(left.x, left.y);
    double delta = calculateDelta(p1, p2);
    if (delta < tolerance_) {
      traversal_->add(left);
    }
  }

  if(check(above)){
    HSLAPixel & p2 = png_.getPixel(above.x, above.y);
    double delta = calculateDelta(p1, p2);
    if (delta < tolerance_) {
      traversal_->add(above);
    }
  }



  while(!traversal_->empty()&&(traversal_->getVisited(traversal_->peek()))){
    traversal_->pop();
  }

  if(traversal_->empty()) {
    finished_ = true;
    return *this;
  } else {

    current_ = traversal_->peek();
    return *this;
  }
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(finished_ && other.finished_);

}

//ImageTraversal::~ImageTraversal() {}
