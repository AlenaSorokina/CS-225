
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG png;      png.readFromFile("flower.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(png.width()/2,png.height()/2), 0.2);
  DFS dfs(png, Point(png.width()/4,png.height()/4), 0.2);
  DFS dfs1(png, Point(png.width()/4,png.height()*3/4), 0.2);
  DFS dfs2(png, Point(png.width()*3/4,png.height()/4), 0.2);
  DFS dfs3(png, Point(png.width()*3/4,png.height()*3/4), 0.2);
  DFS dfs4(png, Point(png.width()/2,png.height()*3/4), 0.2);
  HSLAPixel color(219, 1, 0.5);
  HSLAPixel color2(23, 1, 0.5);
  SolidColorPicker solid(color);
  SolidColorPicker solid2(color2);
  RainbowColorPicker rain(0.05);


  MyColorPicker my(color, color2, Point(png.width()/2+10,png.height()/2-10));
  image.addFloodFill( bfs, my );
  image.addFloodFill( dfs, solid2 );
  image.addFloodFill( dfs1, solid );
  image.addFloodFill( dfs2, rain );
  image.addFloodFill( dfs3, solid );
  image.addFloodFill( dfs4, solid2 );

  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
