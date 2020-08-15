/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (curDim < 0 || curDim >= Dim) return false;
     if (first[curDim]<second[curDim]){
       return true;
     } else if (first[curDim]==second[curDim]){
       return (first<second);
     }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     if(distance(target, potential) < distance(target, currentBest)) {
       return true;
     } else if (distance(target, potential) > distance(target, currentBest)){
       return false;
     } else
     return (potential < currentBest);
}

template <int Dim>
int KDTree<Dim>::distance(const Point<Dim>& first, const Point<Dim>& second) const{
  int dist = 0;
  for(int i = 0; i<Dim; i++) {
    dist += (first[i]-second[i])*(first[i]-second[i]);
  }
  return dist;
}


template <int Dim>
void KDTree<Dim>::swap(Point<Dim> first, Point<Dim> second){
  Point<Dim> temp = first;
  first = second;
  second = temp;
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, int dim, unsigned left, unsigned right, unsigned pivotIndex) {
  Point<Dim> x = list[pivotIndex];
  unsigned i = left;
  Point<Dim> temp = list[pivotIndex];
  list[pivotIndex] = list[right];
  list[right] = temp;
  for(unsigned j = left; j<right; j++) {
    if(smallerDimVal(list[j], x, dim)) {
      temp = list[i];
      list[i] = list[j];
      list[j] = temp;
      i++;
    }
  }
  temp = list[i];
  list[i] = list[right];
  list[right] = temp;
  return i;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(vector<Point<Dim>>& list, int dim, unsigned left, unsigned right, unsigned n) {
  if(left == right) {
    return list[left];
  }
  unsigned pivotIndex = n;
  pivotIndex = partition(list, dim, left, right, pivotIndex);
  if(n == pivotIndex) return list[n];
  else if (n<pivotIndex) return quickselect(list, dim, left, pivotIndex-1, n);
  else return quickselect(list, dim, pivotIndex+1, right, n);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::ctor(vector<Point<Dim>>& points,int dim, unsigned left, unsigned right){
  if(points.empty() || left<0 || right<0|| left >=points.size() || right>=points.size()|| left>right) {
    return NULL;
  }
  unsigned pivotIndex = (left+right)/2;

  KDTreeNode* subroot = new KDTreeNode(quickselect(points,dim%Dim,left,right,pivotIndex));
  size+=1;
  dim++;
  subroot->left = ctor(points, dim, left, pivotIndex-1);
  subroot->right = ctor(points, dim, pivotIndex+1, right);
  return subroot;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = 0;
    vector<Point<Dim>> v;
    v.assign(newPoints.begin(), newPoints.end());
    root = ctor(v, 0, 0, v.size()-1);

}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode* subroot, KDTreeNode* other_subroot) {
  subroot = new KDTreeNode();
  subroot->point = other_subroot->point;
  copy(subroot->left, other_subroot->left);
  copy(subroot->right, other_subroot->right);
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
   copy(this->root, other.root);
   size = other.size;
}



template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot) {
	if (subroot == NULL) return;
	if (subroot->left != NULL) clear(subroot->left);
	if (subroot->right != NULL) clear(subroot->right);
	delete subroot;
	subroot = NULL;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  if(this!=NULL) {
    clear(root);
  }
  copy(this->root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query,KDTreeNode* currentNode, int currDim) const {
  if(currentNode->left == NULL && currentNode->right == NULL) {
    return currentNode->point;
  }
  int nextDim = (currDim+1)%Dim;
  Point<Dim> currClosest = currentNode->point;
  Point<Dim> potential = currClosest;
  bool next = smallerDimVal(query, currClosest, currDim);
  if(next && currentNode->left!=NULL) {
    potential = findNearestNeighbor(query, currentNode->left, nextDim);
  } else if (!next && currentNode->right!=NULL) {
    potential = findNearestNeighbor(query, currentNode->right, nextDim);
  }

  if(shouldReplace(query, currClosest, potential)) {
    currClosest = potential;
  }

  int radius = distance(query, currClosest);
  int dimRadius = (query[currDim] - currentNode->point[currDim])*(query[currDim] - currentNode->point[currDim]);

  if(dimRadius<=radius) {
    if(!next && currentNode->left!=NULL) {
      potential = findNearestNeighbor(query, currentNode->left, nextDim);
      if(shouldReplace(query, currClosest, potential)) {
        currClosest = potential;
      }
    } else if (next && currentNode->right!=NULL) {
      potential = findNearestNeighbor(query, currentNode->right, nextDim);
      if(shouldReplace(query, currClosest, potential)) {
        currClosest = potential;
      }
    }
  }

  return currClosest;

}
