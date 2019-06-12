/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  if (head_!=NULL){
  ListNode * temp = head_;
  while (temp->next!=NULL)
  { temp = temp->next;
    delete temp->prev;
    length_--;
  }
}
    if(tail_!=NULL)
    delete tail_;
    head_ = NULL;
    tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode * node = new ListNode(ndata);
  if (head_ == NULL){
    head_ = node;
    //prev default to null
    tail_ = head_;

  }
  else{
  node ->next = head_;
  node ->prev = NULL; //technically not needed
  head_ ->prev = node;
  head_ = node;
}
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * node = new ListNode(ndata);
  if (tail_ == NULL){
    tail_ = node;
    head_ = tail_;
  }
  else{
  tail_ ->next = node;
  node ->next = NULL;
  node ->prev = tail_;
  tail_ = node;
}
  length_++;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
//  ListNode * temp1;
//  ListNode * temp2;

  ListNode * a = startPoint;
  ListNode * b = NULL;
  ListNode * c = endPoint;
  startPoint = endPoint;
  endPoint = a;
  if ((startPoint == NULL) || (endPoint ==NULL) || (startPoint == endPoint)){
    return;
  }
  while(b!=c){
    b = a;
    a = a->next;
    b->next = b->prev;
    b->prev = a;
  }

if(startPoint == tail_){
    tail_ = endPoint;
  }
if (endPoint == head_){
  head_ = startPoint;
}


if(endPoint->next!=NULL){
  endPoint ->next ->next = startPoint;
  startPoint ->prev = endPoint->next;}

else startPoint->prev =NULL;

if(a!=NULL)
  {endPoint->next = a;
  a->prev = endPoint;}

else endPoint->next=NULL;
return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  ListNode * a = head_;
  ListNode * b;
  ListNode * temp;
  if ((head_==NULL)||(n<=1)){return;}
  if (n>=length_){
  reverse();
  return;}
  while(a !=NULL){
    int k;
    b = a;
    for(k=1;k<n;k++){
      if(b->next==NULL){break;} //last chunk ends short
      b = b->next;
        }
    temp = b->next;
    reverse(a, b);
    a = temp;
  }


}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
//ListNode * temp1;
//ListNode * temp2;

ListNode * a = head_->next;
ListNode * b = head_;
while(a!=tail_){
  b->next = a->next;
  a->next->prev = b;
  a->next = NULL;
  a->prev = tail_;
  tail_->next = a;
  tail_ = a;
if(b->next->next!=NULL){
  b=b->next->next;
  a=b;
  b=b->prev;
}
else{
  if(b->next==NULL) return;
}
}
return;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */




template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  ListNode * temp = start;
  for (int i = 0; i<splitPoint; i++){
    if(temp->next!=NULL){
    temp = temp->next;}
    if(temp->next == NULL)
    break;
  }
  temp->prev->next = NULL;
  tail_ = temp->prev;
  temp->prev = NULL;


  return temp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;

    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first==NULL&&second==NULL) return NULL;
  if(second==NULL) return first;
  if(first==NULL) return second;

  ListNode * a = first;
  ListNode * b = second;
  ListNode * c = NULL;
//  ListNode * p = NULL;
//  ListNode * q = NULL;

//take care of head case
  if((b->data)<(a->data)){
    c = b;
    b = b->next;
  }
  else{
    c = a;
    a = a->next;
  }
  // so now c holds the list that starts smaller
  //four cases, a is NULL or b is NULL, a<b, b<a
  while (!(a==NULL) || !(b==NULL)){
    if(b==NULL){ //if nothing in b, insert node from a
      c->next = a;
      a->prev = c;
      c = c->next;
      a = a ->next;}
    else if(!(a==NULL)&&((a->data)<(b->data))){
      //if something in b and a, and a<b, insert node from a
          c->next = a;
          a->prev = c;
          c = c->next;
          a = a ->next;
        }
// if nothing in a, or b<a, insert node from b
    else {
          c->next = b;
          b->prev = c;
          c = c->next;
          b = b ->next;
    }
  }
//return based on head case
 if((first->data)<(second->data)) return first;
  return second;
}
/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if(start==NULL){return NULL;}
  if(chainLength<=1){return start;}
  int len = chainLength/2;
  ListNode * a = start;
  ListNode * b = split(start, len);
  if(chainLength%2==1){
  a=mergesort(a, len);
  b=mergesort(b, len+1);}
  else {
    a=mergesort(a, len);
    b=mergesort(b, len);
  }

  return merge(a, b);
}

/*  ListNode * a = start;
  int len = chainLength/2;
  ListNode * b = start;
  //ListNode * c;
  int counter = 0;
  while(counter<len){
    if(b->next!=NULL)
    b=b->next;
    counter++;
  }
  if(chainLength%2==1){
  a=mergesort(a, len);
  b=mergesort(b, len+1);}
  else {
    a=mergesort(a, len);
    b=mergesort(b, len);
  }

  return merge(a, b);}*/
