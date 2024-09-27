#include "scheduler.h"

#include <iostream>

#include "core.h"
#include "message.hpp"
#include "tasklinkedlist.h"
#include "task.h"

using namespace std;

Scheduler::Scheduler() { head_ = nullptr;  time_ = 0;}

Scheduler::~Scheduler() { Message::SCHEDULER_REMOVED.PrintMessage(); }

void Scheduler::TickTock(int time) {
  time_ = time_ + time;
  while (head_ != nullptr) {
    head_->TickTock(time);
    head_ = head_->GetNextCore();
  }
}
