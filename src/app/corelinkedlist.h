#ifndef CORELINKEDLIST_H
#define CORELINKEDLIST_H

#include "core.h"
#include "task.h"

class CoreLinkedList {
 public:
  CoreLinkedList();
  ~CoreLinkedList();
  void Add(Core* new_core);
  void Remove(Core* core_to_delete);
  void AddTask(Task* task_to_add);
  Core* GetCore(std::string core_id) const;
  Core* GetHead() const;

 private:
  Core* head_;
};

#endif
