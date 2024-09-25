#include <iostream>
#include "core.h"
#include <string>
#include "task.h"
#include "message.hpp"
#include "priority.h"

using namespace std;

Priority::Priority(std::string core_id) : Core(core_id)
{

}

Priority::Priority() {
  
}

Priority::~Priority()
{
  Message::CORE_REMOVED.PrintMessage({to_string(GetCoreId())});
}