#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "core.h"

class Scheduler {
 public:
  Scheduler();
  ~Scheduler();
  void TickTock(int time);

 private:
  Core* head_;
  int time_;
};

#endif
