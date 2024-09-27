#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
 public:
  Task();
  Task(const std::string id, const std::string time,
       const std::string priority);
  ~Task();
  int GetTaskId() const;
  Task* GetNextTask() const;
  void SetNextTask(Task* next_task);
  void SetTaskDuration(int duration_to_set);
  int GetTaskDuration() const;
  void TickTock(int time);

 private:
  int task_id_;
  int duration_;
  int priority_;
  Task* next_;
};

#endif
