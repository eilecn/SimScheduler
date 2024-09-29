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
  Task* temp = core_tasks_->GetHead();;
  if (temp == nullptr) {
    core_tasks_->SetHead(task);
    assigned_tasks_++;
    return;
  }

  if (task->GetPriority() < temp->GetPriority()) {
    task->SetNextTask(core_tasks_->GetHead());
    core_tasks_->SetHead(task);
    assigned_tasks_++;
    return;
  }

  Task* current = core_tasks_->GetHead();
  while (current->GetNextTask() != nullptr &&
         current->GetNextTask()->GetPriority() <= task->GetPriority()) {
    current = current->GetNextTask();
  }

  task->SetNextTask(current->GetNextTask());
  current->SetNextTask(task);
  assigned_tasks_++;
}
