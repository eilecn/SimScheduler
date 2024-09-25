#include "scheduler.h"

#include <iostream>
#include "message.hpp"
#include "core.h"

using namespace std;

Scheduler::Scheduler() {
  head = nullptr;
}

Scheduler::~Scheduler() {
  Message::SCHEDULER_REMOVED.PrintMessage();
}
