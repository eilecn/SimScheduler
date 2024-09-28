#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
 public:
  Task();
  Task(const std::string id, const std::string time, const std::string priority,
       const std::string arrival_time);
  ~Task();
  int GetTaskId() const;
  Task* GetNextTask() const;
  void SetNextTask(Task* next_task);
  void SetTaskDuration(int duration_to_set);
  int GetTaskDuration() const;
  int GetOriginalTaskDuration() const;
  int GetPriority() const;
  void SubractOneTick();
  void IncrementTimeInSystem();
  int GetTimeInSystem() const;
  int GetArrivalTime() const;

 private:
  int task_id_;
  int duration_;
  int priority_;
  Task* next_;
  int original_duration_;
  int time_in_system_;
  int arrival_time_;
};

#endif
