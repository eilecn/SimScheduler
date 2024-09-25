#ifndef NODE_H
#define NODE_H

#include <string>

#include "core.h"

class Task {
 public:
  Task();
  Task(const std::string id, const std::string time,
       const std::string priority);
  ~Task();
  int GetTaskId() const;
  Task* GetNextTask() const;
  void SetNextTask(Task* next_task);

 private:
  int task_id_;
  int duration_;
  int priority_;
  Task *next;
};

#endif
