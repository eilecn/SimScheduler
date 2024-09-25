#include <iostream>
#include "core.h"
#include <string>
#include "task.h"
#include "message.hpp"
#include "fifo.h"

using namespace std;

Fifo::Fifo(std::string core_id) : Core(core_id)
{

}

Fifo::Fifo()
{
  
}

Fifo::~Fifo()
{
  Message::CORE_REMOVED.PrintMessage({to_string(GetCoreId())});
}