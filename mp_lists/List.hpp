/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

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
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
        // iterate down the parameter list
  while (curr != NULL) {
    ListNode* temp = curr->next;
    delete curr;
    curr = temp;

  }
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
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if(head_==NULL && tail_ == NULL) {
    tail_=newNode;
    head_=newNode;
    length_++;
    return;
  }

  head_ -> prev = newNode;
  newNode -> next = head_;
  newNode -> prev = NULL;
  head_ = newNode;
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
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if(head_==NULL && tail_ == NULL) {
    tail_=newNode;
    head_=newNode;
    length_++;
    return;
  }

  tail_ -> next = newNode;
  newNode -> next = NULL;
  newNode -> prev = tail_;
  tail_ = newNode;
  length_++;
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
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(start == NULL||start->next == NULL) {
    return start;
  }

  if(splitPoint==0) {
    return start;
  }


  if(splitPoint>=length_) {
    return start;
  }
  ListNode * curr = start;

  for (int i = 0; i < splitPoint; i++) {
    if(curr->next !=NULL) {
      curr = curr->next;
    } else {
      return start;
    }

  }

  if (curr != NULL) {
      tail_ = curr->prev;
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
   //@todo Graded in MP3.1
  ListNode * curr = head_;

  int a = length_/3;
  if (a>0) {
    head_= head_->next;
    head_->prev= NULL;
  }

  for(int i=0; i<a; i++) {
      if (curr->prev !=NULL){
        curr->prev->next=curr->next;
        curr->next->prev = curr->prev;
      } else {
        curr->next->prev=NULL;
      }
      if(curr->next->next->next==NULL) {
        curr->prev = curr->next->next;
        curr->prev->next = curr;
        curr->next = NULL;

      } else {
        curr->next=curr->next->next->next;
        curr->prev=curr->next->prev;
        curr->next->prev = curr;
        curr->prev->next = curr;
      }

      curr = curr->next;
    }


  if (curr == NULL) {
    tail_=tail_->next;
  }
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
  /// @todo Graded in MP3.2

    ListNode *current = startPoint;
    ListNode* startprev = startPoint->prev;
    ListNode *endnext = endPoint->next;
    ListNode *temp;



    if(startPoint == endPoint) {
      return;
    }



    if(startPoint == NULL ||  endPoint == NULL) {
      return;
    }


    while (current != endnext)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if(startprev != NULL) {
      startprev->next = endPoint;
      endPoint->prev = startprev;
    } else {
      endPoint->prev = NULL;
      //head_= endPoint;
    }

    if(endnext !=NULL) {
      startPoint->next = endnext;
      endnext->prev = startPoint;
    } else {
      startPoint->next = NULL;
      //tail_ = startPoint;
    }

    temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;

    if (head_ == endPoint) {
      head_ = startPoint;
    }
    if (tail_ == startPoint) {
      tail_ = endPoint;
    }


}




/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n<=1) {
    return;
  }
  if(n>=length_){
    reverse (head_, tail_);
    return;
  }
  ListNode *curr_start = head_;
  //bool a = true;
  //ListNode *curr_end = head_;

  while(curr_start !=NULL)
 {
   ListNode *curr_end = curr_start;
   for (int i = 1; i<n; i++) {
     if (curr_start!=tail_) {
        curr_start = curr_start->next;
     } else {
       reverse(curr_end, tail_);
       return;
     }
   }
   reverse(curr_end, curr_start);
   curr_start = curr_start->next;

 }

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
  /* a dummy first node to hang the result on */
  if (first == NULL && second == NULL) {
    return NULL;
  }
  if (first == NULL) {
    return second;
  }

  if (second == NULL) {
    return first;
  }

  ListNode *curr;
  ListNode *temp;

  if( first->data < second->data) {
    curr = first;
    first = first->next;
  } else {
    curr = second;
    second = second->next;
  }

  temp = curr;
  while (first!=NULL && second !=NULL) {
    if( first->data < second->data) {
      temp->next = first;
      first->prev = temp;
      first = first->next;
    } else {
      temp->next = second;
      second->prev = temp;
      second = second->next;
    }
    temp = temp->next;
  }

  if(first==NULL && second !=NULL){
    temp->next = second;
    second->prev = temp;
    second = second->next;
    temp = temp->next;
  }

  if(first!=NULL && second ==NULL){
    temp->next = first;
    first->prev = temp;
    first = first->next;
    temp = temp->next;
  }

  return curr;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength ==1 ){
    return start;
  } else {
    int len = chainLength/2;
    ListNode* curr;
    curr = split(start, len);
    ListNode* first = mergesort(start, len);
    ListNode* second = mergesort(curr,chainLength-len);
    return merge(first, second);
}
}
