#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze m;
    m.makeMaze(50, 50);

    cs225::PNG* creative = m.drawCreativeMaze();
    creative->writeToFile("creative.png");
    delete creative;
    
    return 0;

}
