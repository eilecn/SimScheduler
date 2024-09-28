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
  void SetHead(Task* task);

 private:
  Task* head_;
  int execution_time_;
};

#endif
