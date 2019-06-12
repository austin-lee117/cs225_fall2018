/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;
#include <vector>

//checks if first<second at given dimension
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     bool ret = false;
     if(first[curDim]<second[curDim]){ //if less than then true!
       ret = true;
     }
     else if(first[curDim]==second[curDim]){ //if equal then also true!
       if(first<second){
         ret = true;
       }
     }

    return ret;
}
//checks if potential is a smaller distance away from target
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int dim = Dim; //dimnsion of compared points
     double d1 = 0; // distance of currentBest
     double d2 = 0; // distance of potential
     bool ret = false;
     for (int i = 0; i< dim; i++){
       double x = currentBest[i] - target[i];
       x = x*x;
       double y = potential[i] - target[i];
       y = y*y;
       d1+=x;
       d2+=y;
     } // add square of distance between each dimension
     if(d2<d1){
       ret = true;
     }
     else if(d2==d1){
       if(potential<currentBest){
         ret = true;
       }
     }
     return ret;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if (newPoints.size()==0){
       size = 0;
       root = NULL;
     }
     else{
       size = newPoints.size();
       vect = newPoints;
       root = buildTree(vect, 0, vect.size()-1, 0);
     }
}
template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>&vect, int min, int max, int dim){
  if(min>max) return NULL; //base/end case
  int med = (min+max)/2; //median value
  helper(vect, min, max, med, dim);
  KDTreeNode * node = new KDTreeNode(vect[med]); //create new internal node
  dim = (dim+1)%Dim; //update dimension
  node->left = buildTree(vect, min, med-1, dim); //create left subtree
  node->right = buildTree(vect, med+1, max, dim); //create right subtree
  return node;
}

//helper function to partition and sort the vector based on dimension around a pivot
template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>&vect, int min, int max, int med, int dim){
  Point<Dim> pivot = vect[med];
  Point<Dim> end = vect[max];
  vect[max] = pivot;
  vect[med] = end;
  //swapping max point with given median point
  int i = min; //setting up parameters
  for(int j = min; j<max; j++){
    if(smallerDimVal(vect[j], pivot, dim)){
      //swap(vect[i], vect[j]);
      Point<Dim> temp = vect[i];
      vect[i] = vect[j];
      vect[j] = temp;
      i++;
    } //swap all values less than pivot point
    }
  //swap(vect[i], vect[max]);
  //final swap
  Point<Dim> temp = vect[max];
  vect[max] = vect[i];
  vect[i] = temp;
  return i;
}

//helper function to find the median
template<int Dim>
void KDTree<Dim>::helper(vector<Point<Dim>>&vect, int min, int max, int median, int dim){
  if(min == max) return; //base/end case
  int index = partition(vect, min, max, median, dim);
  if(index == median){
    return; // if index is the same as median
  }
  else if(median < index){ // if index is greater than the median
    helper(vect, min, index-1, median, dim);
    return;
  }
  else{
    helper(vect, index+1, max, median, dim); //else index is less than median
    return;
}
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   vect = other.vect;
   size = other.size;
   root = buildTree(vect, 0, vect.size()-1, 0);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if(this!=&rhs){
     annihilate_to_shreds_and_pieces(this);
     vect = rhs.vect;
     size = rhs.size;
     root = buildTree(vect, 0, vect.size()-1, 0);
   }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   annihilate_to_shreds_and_pieces(root);
}
template<int Dim>
void KDTree<Dim>::annihilate_to_shreds_and_pieces(KDTreeNode * root){
  if(root!=NULL){
    if(root->left!=NULL){
      annihilate_to_shreds_and_pieces(root->left);
    }
    if(root->right!=NULL){
      annihilate_to_shreds_and_pieces(root->right);
    }
    delete root;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     return assistant(root, query, root->point, 0);

  }
template<int Dim>
Point<Dim> KDTree<Dim>::assistant(KDTreeNode* curr, Point<Dim>want, Point<Dim>ret, int dim) const {
  bool left = false;
  Point<Dim> currentBest;
  if(curr->left==NULL && curr->right==NULL){ //if we are at a leaf node, there are no better options
    ret = curr->point;
    return ret;
  }

  if(smallerDimVal(want,curr->point,dim)){
    if(curr->left!=NULL){
      //dim = (dim+1)%Dim; // do the incrementation in the recursion call
      ret = assistant(curr->left, want, ret, (dim+1)%Dim); // recurse into the left subtree;
      left = true;
    }
  }
  if(smallerDimVal(curr->point, want, dim)){
    if(curr->right!=NULL){
      //dim = (dim+1)&Dim;
      ret = assistant(curr->right, want, ret, (dim+1)%Dim); //recurse into the right subtree;
    }
  }
  double retwantdist = 0; //distance between ret and want
  for (int i = 0; i < Dim; i++){
    double x = want[i] - ret[i];
    x = x*x;
    retwantdist+=x;
  }
  double currwantdist = (curr->point)[dim] - want[dim]; //distance between curr and want
  currwantdist = currwantdist*currwantdist;
  if(currwantdist<=retwantdist){
    if(left){ //left exists
      if(curr->right!=NULL){ //if right exists check right
        currentBest = assistant(curr->right, want, ret, (dim+1)%Dim);
        if(shouldReplace(want, ret, currentBest)){ //if currentBest is closer then use
          ret = currentBest;
        }
      }
    }
    else{
      if(curr->left!=NULL){ //if left exists check left
      currentBest = assistant(curr->left, want, ret, (dim+1)%Dim);
      if(shouldReplace(want, ret, currentBest)){ //if currentBest is closer then use
        ret = currentBest;
      }
    }
  }
}
  if(shouldReplace(want, ret, curr->point)){
    ret = curr->point;
  }

return ret;

}
