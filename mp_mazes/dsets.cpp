/* Your code here! */
#include "dsets.h"
#include <iostream>


/*Creates num unconnected root nodes at the end of the vector.*/

void DisjointSets::addelements(int num) {
  for(int i=0; i<num; i++){
    sets.push_back(-1);
  }
}


/* the find function on element returns the name
 of the disjoint set where this element belongs
 and sets that element and all of its ancestors
 to point directly to the root.*/

int DisjointSets::find(int elem) {
  if ( sets[elem] < 0 ) {
    return elem;
  } else {
    int ans =  find(sets[elem]);
    sets[elem] = ans;
    return ans;
  }
}



void DisjointSets::setunion(int a, int b){
  int first = find(a);
  int second = find(b);
  if (first == second) return;

  if(sets[first] > sets[second]) {
    sets[second] = sets[first]+ sets[second];
    sets[first] = second;
  } else {
    sets[first] = sets[first]+ sets[second];
    sets[second] = first;
  }
}

int	DisjointSets::size(int elem) {
  int temp = find(elem);
  return (-1)*sets[temp];
}
