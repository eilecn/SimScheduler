#include "scheduler.h"

#include <iostream>

#include "core.h"
#include "message.hpp"

using namespace std;

Scheduler::Scheduler() { head = nullptr; }

Scheduler::~Scheduler() { Message::SCHEDULER_REMOVED.PrintMessage(); }
