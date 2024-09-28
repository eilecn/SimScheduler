#ifndef TASKLINKEDLIST_H
#define TASKLINKEDLIST_H

#include "task.h"

class TaskLinkedList {
 public:
  TaskLinkedList();
  ~TaskLinkedList();
  Task* GetTask(std::string task_id) const;
  int GetExecutionTime() const;
  Task* GetHead() const;
  void RemoveTask(Task* task_to_remove);

 private:
  Task* head_;
  int execution_time_;
};

#endif
