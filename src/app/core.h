#ifndef CORE_H
#define CORE_H
#include <string>

#include "task.h"
#include "tasklinkedlist.h"

class Core {
 public:
  Core();
  Core(std::string core_id);
  ~Core();
  int GetCoreId() const;
  Core* GetNextCore() const;
  void SetNextCore(Core* next_core);
  void TickTock();
  int GetPendingExecutionTime() const;
  virtual void AddTask(Task* task);
  Task* GetFirstTask() const;
  virtual void RemoveTask(Task* task);
  Task* GetTask(std::string task_id) const;
  int GetAssignedTasksNumber() const;
  int GetCompletedTasksNumber() const;

 private:
  int core_id_;
  Core* next_;
  TaskLinkedList* core_tasks_;
  Task* first_task_;
  int pending_execution_time_;
  int assigned_tasks_;
  int completed_tasks_;
};

#endif
