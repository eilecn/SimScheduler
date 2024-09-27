#include "fifo.h"

#include <iostream>
#include <string>

#include "core.h"
#include "message.hpp"
#include "task.h"

using namespace std;

Fifo::Fifo(std::string core_id) : Core(core_id) {
}

Fifo::Fifo() {}

Fifo::~Fifo() { Message::CORE_REMOVED.PrintMessage({to_string(GetCoreId())}); }
