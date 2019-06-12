/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template<class K, class V>
int AVLTree<K, V>::Max(Node* a, Node* b){
  int x = heightOrNeg1(a);
  int y = heightOrNeg1(b);
  if(x>=y) return x;
  if(y>x) return y;
  return x;
}


template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here


    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t->height = Max(t->left, t->right) + 1;
    temp->height = Max(temp->left, temp->right) + 1;
    t = temp;


    return;

}
template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = Max(t->left, t->right) + 1;
    temp->height = Max(temp->left, temp->right) + 1;
    t = temp;

    return;
}


template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}
template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}


template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree==NULL) return;

    int righty = heightOrNeg1(subtree->right);
    int lefty = heightOrNeg1(subtree->left);

   if (righty-lefty<=-2){
      if(heightOrNeg1(subtree->left->left)>=heightOrNeg1(subtree->left->right)){
        rotateRight(subtree);
      }
      else rotateLeftRight(subtree);
    }
    else if (righty-lefty>=2){
      if(heightOrNeg1(subtree->right->right) >= heightOrNeg1(subtree->right->left)){
        rotateLeft(subtree);
      }
      else rotateRightLeft(subtree);
    }
    subtree->height = Max(subtree->right, subtree->left) +1;
  }

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL){ subtree = new Node(key, value);
    return;}
    else if(key<subtree->key){
      insert(subtree->left, key, value);
      rebalance(subtree);
    }
    else if(key>subtree->key){
      insert(subtree->right, key, value);
      rebalance(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
      remove(subtree->left, key);
          rebalance(subtree);

    } else if (key > subtree->key) {
      remove(subtree->right, key);
          rebalance(subtree);

    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {

            Node * temp = subtree->left;
            while(temp->right!=NULL){
              temp = temp->right;
            }
            subtree->key = temp->key;
            subtree->value = temp->value;
            remove(subtree->left, temp->key);
        } else {
          if(subtree->left==NULL){
            Node * tempa = subtree->right;
            delete subtree;
            subtree = tempa;
          }
          if(subtree->right==NULL){
            Node * tempa = subtree->left;
            delete subtree;
            subtree = tempa;
          }
        }
          rebalance(subtree);
    }

}
