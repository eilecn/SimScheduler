#include "core.h"

#include <iostream>
#include <string>

#include "message.hpp"
#include "task.h"
#include "tasklinkedlist.h"

using namespace std;

Core::Core(std::string core_id) {
  core_id_ = stoi(core_id);
  next_ = nullptr;
  core_tasks_ = TaskLinkedList().GetHead();
  time_ = 0;
}

Core::Core() {}

Core::~Core() { Message::CORE_REMOVED.PrintMessage({to_string(core_id_)}); }

int Core::GetCoreId() const { return core_id_; }

Core* Core::GetNextCore() const { return next_; }

void Core::SetNextCore(Core* next_core) { next_ = next_core; }

void Core::TickTock(int time) {
  time_ = time_ + time;
  while (next_ != nullptr) {
    // ticktock on tasklinkedlist
  }
}
