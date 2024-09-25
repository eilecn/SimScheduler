#include "priority.h"

#include <iostream>
#include <string>

#include "core.h"
#include "message.hpp"
#include "task.h"

using namespace std;

Priority::Priority(std::string core_id) : Core(core_id) {}

Priority::Priority() {}

Priority::~Priority() {
  Message::CORE_REMOVED.PrintMessage({to_string(GetCoreId())});
}