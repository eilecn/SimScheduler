#ifndef CORELINKEDLIST_H
#define CORELINKEDLIST_H

#include "core.h"

class CoreLinkedList {
 public:
  CoreLinkedList();
  ~CoreLinkedList();
  void Add(Core* new_core);
  void Remove(Core* core_to_delete);
  Core* GetCore(std::string core_id) const;
  Core* GetHead() const;

 private:
  Core* head_;
  Task* core_tasks_;
};

#endif
