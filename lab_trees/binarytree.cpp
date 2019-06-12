/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
mirror(root);
}


template <typename T>
void BinaryTree<T>::mirror(Node* x){ //helper function for the mirror function
  if(x ==NULL){return;}
    Node * l = x->left;
    x->left = x->right;
    x->right = l;
    mirror(x->left);
    mirror(x->right);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code
    InorderTraversal<T> iot(root);
    typename TreeTraversal<T>::Iterator a = iot.begin();
    typename TreeTraversal<T>::Iterator b = a;
    ++a;
    while(a!=iot.end()){
      if((*a)->elem < (*b)->elem)
      return false;
      b = a;
      ++a;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    if(root==NULL){return true;}
    //bool a = isOrderedRecursive(root, root->elem);
    bool b = isOrderedRecursive(root);
  //  if(a&&b) return true;
    return b;
}
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* x) const{
  BinaryTree<T>::Node* curr = x;
  bool yesno = true;
  if(curr->right!=NULL){
    if(curr->elem>curr->right->elem)
    return false;
    else yesno = yesno && isOrderedRecursive(curr->right);
  }
  if(curr->left!=NULL){
    if(curr->elem<curr->left->elem)
    return false;
    else yesno = yesno && isOrderedRecursive(curr->left);
  }
  return yesno;
}
/*template <typename T>
bool BinaryTree<T>::isOrderedRecursiveLeft(Node* x, T z) const{}
typename BinaryTree<T>::Node* curr = x;
  bool lefty = false;
  if(curr==NULL){return true;}
  if(curr->left==NULL && curr->right==NULL){return true;}
  if((curr->left->elem < curr ->elem)&&(curr->left->elem<z)){
    lefty = true;
  }
  lefty = lefty && isOrderedRecursiveLeft(curr->left, z) && isOrderedRecursiveRight(curr->right, z);
  return lefty;

}*/

/*template <typename T>
bool BinaryTree<T>::isOrderedRecursiveRight(Node * x, T y) const
{ typename BinaryTree<T>::Node* curr = x;
  bool righty = false;
  if(curr==NULL){return true;}
  if(curr->left==NULL && curr->right==NULL){return true;}
  if((curr->elem < curr->right->elem)&&(y<curr->right->elem)){
    righty = true;
}
  righty = righty && isOrderedRecursiveLeft(curr->left, y) && isOrderedRecursiveRight (curr->right, y);
  return righty;
}*/

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(vector<vector<T> > &paths) const
{
    // your code here
    vector<T> vec;
    getPaths(root, vec, paths);
}

template <typename T>
void BinaryTree<T>::getPaths(Node* x, vector<T> vec, vector<vector<T> > &paths) const{
    BinaryTree<T>::Node* curr = x;
    if(curr==NULL){return;}
    if(curr->right==NULL){
      if(curr->left==NULL){
      vec.push_back(curr->elem);
      paths.push_back(vec);
      return;
    }}
      vec.push_back(curr->elem);
      if(curr->left!=NULL)
      getPaths(curr->left, vec, paths);
      if(curr->right!=NULL)
      getPaths(curr->right, vec, paths);
      }
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int totality = 0;
    int edges = 0;
    totality = sumDistances(totality, edges, root);
    return totality;
}
template <typename T>
int BinaryTree<T>::sumDistances(int &totality, int edges, Node* root) const{
  if(root==NULL)return 0;
  totality += edges;
  edges = edges+1;
  sumDistances(totality, edges, root->left);
  sumDistances(totality, edges, root->right);
  return totality;
}
