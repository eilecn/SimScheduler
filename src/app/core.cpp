#include <iostream>
#include "core.h"
#include <string>
#include "task.h"
#include "message.hpp"

using namespace std;

Core::Core() {
}

Core::Core(std::string core_id) {
  core_id_ = stoi(core_id);
  next = nullptr;
  }

Core::~Core() {
  Message::CORE_REMOVED.PrintMessage({to_string(core_id_)});
}

int Core::GetCoreId() const { return core_id_; }

Core* Core::GetNextCore() const {
  return next;
}

void Core::SetNextCore(Core* next_core) {
  next = next_core;
}
