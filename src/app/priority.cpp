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

void Priority::AddTask(Task* task) {
  if (first_task_ == nullptr) {
    first_task_ = task;
    assigned_tasks_++;
    return;
  }

  if (task->GetPriority() > first_task_->GetPriority()) {
    task->SetNextTask(first_task_);
    first_task_ = task;
    assigned_tasks_++;
    return;
  }

  Task* current = first_task_;
  while (current->GetNextTask() != nullptr &&
         current->GetNextTask()->GetPriority() >= task->GetPriority()) {
    current = current->GetNextTask();
  }

  task->SetNextTask(current->GetNextTask());
  current->SetNextTask(task);
  assigned_tasks_++;
}
