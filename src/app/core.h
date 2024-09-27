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
  void TickTock(int time);

 private:
  int core_id_;
  Core* next_;
  TaskLinkedList* core_tasks_;
  int time_;
  Task* first_task_;
};

#endif
