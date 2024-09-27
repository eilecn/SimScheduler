#ifndef TASKLINKEDLIST_H
#define TASKLINKEDLIST_H

#include "task.h"

class TaskLinkedList {
 public:
  TaskLinkedList();
  ~TaskLinkedList();
  virtual void Add(Task* new_task);
  void Remove(Task* task_to_delete);
  Task* GetTask(std::string task_id) const;
  int GetExecutionTime() const;
  Task* GetHead() const;
  void TickTock(int time);

 private:
  Task* head_;
  int time_;
  int execution_time_;
};

#endif
