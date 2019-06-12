#include "abstractsyntaxtree.h"
using namespace std;
#include <cstring>
#include <cmath>

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @Your code goes here...


    return evaluationresult(root);
}
double AbstractSyntaxTree::evaluationresult(Node* root) const{
  if(root->left==NULL&&root->right==NULL) return stod(root->elem);
  if(root==NULL) return 0;
  double result = 0;
  if((root->elem)=="+"){
    result = evaluationresult(root->left) + evaluationresult(root->right);
  }
  if((root->elem)=="-"){
    result = evaluationresult(root->left) - evaluationresult(root->right);
  }
  if((root->elem)=="*"){
    result = evaluationresult(root->left) * evaluationresult(root->right);
  }
  if((root->elem)=="/"){
    result = evaluationresult(root->left) / evaluationresult(root->right);
  }
  return result;
}
