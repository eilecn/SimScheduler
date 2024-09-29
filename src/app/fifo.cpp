#include "fifo.h"

#include <iostream>
#include <string>

#include "core.h"
#include "message.hpp"
#include "task.h"

using namespace std;

Fifo::Fifo(std::string core_id) : Core(core_id) {}

Fifo::Fifo() {}

Fifo::~Fifo() { Message::CORE_REMOVED.PrintMessage({to_string(GetCoreId())}); }

void Fifo::AddTask(Task* task) {
  Task* temp = core_tasks_->GetHead();
  if (temp == nullptr) {
    core_tasks_->SetHead(task);
    assigned_tasks_++;
    return;
  }

  while (temp->GetNextTask() != nullptr) {
    temp = temp->GetNextTask();
  }
  temp->SetNextTask(task);
  assigned_tasks_++;
  return;
}
