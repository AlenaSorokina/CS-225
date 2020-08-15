/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource, vector<TileImage>& theTiles){
  MosaicCanvas* result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
  vector<Point<3>> points;
  map<Point<3>, TileImage*> map;

  for (vector<TileImage>::iterator it = theTiles.begin() ; it != theTiles.end(); it++){
    LUVAPixel pixel = it->getAverageColor();
    Point<3> point = convertToXYZ(pixel);
    points.push_back(point);
    map[point] = &*it;
  }

 KDTree<3> tree(points);

 for(int i = 0; i<result->getRows(); i++){
   for(int j = 0; j<result->getColumns(); j++) {
     LUVAPixel pix = theSource.getRegionColor(i,j);
     Point<3> given = convertToXYZ(pix);
     Point<3> nearest = tree.findNearestNeighbor(given);
     TileImage* best_tile = map[nearest];
     result->setTile(i,j,best_tile);

   }
 }


    return result;
}
