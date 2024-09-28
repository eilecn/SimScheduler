#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "core.h"
#include "corelinkedlist.h"

class Scheduler {
 public:
  Scheduler();
  ~Scheduler();
  void TickTock();
  void AddCore(Core* core_to_add);
  void RemoveCore(Core* core_to_remove);
  Core* GetCore(std::string core_id_to_get) const;
  Core* GetCoreHead() const;
  int GetNumberOfCores() const;

 private:
  int time_;
  CoreLinkedList core_linked_list_;
  int number_of_cores_;
};

#endif
