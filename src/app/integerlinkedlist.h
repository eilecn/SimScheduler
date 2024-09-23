#ifndef INTEGERLINKEDLIST_H
#define INTEGERLINKEDLIST_H
#include "node.h"

class IntegerLinkedList {
 public:
  IntegerLinkedList() : head(nullptr) {};
  ~IntegerLinkedList();

 private:
  Node *head;
  Node *getLast() const {}
};

#endif
