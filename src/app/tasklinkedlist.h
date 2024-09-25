#ifndef TASKLINKEDLIST_H
#define TASKLINKEDLIST_H

#include "task.h"

class TaskLinkedList {
 public:
  TaskLinkedList();
  ~TaskLinkedList();
  void Add(Task* new_task);
  void Remove(Task* task_to_delete);
  Task* GetTask(std::string task_id) const;

 private:
  Task* head;
};

#endif