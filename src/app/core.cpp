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
  core_tasks_ = new TaskLinkedList();
  first_task_ = core_tasks_->GetHead();
  pending_execution_time_ = 0;
  assigned_tasks_ = 0;
  completed_tasks_ = 0;
  time_ = 0;
}

Core::Core() {}

Core::~Core() { Message::CORE_REMOVED.PrintMessage({to_string(core_id_)}); }

int Core::GetCoreId() const { return core_id_; }

Core* Core::GetNextCore() const { return next_; }

void Core::SetNextCore(Core* next_core) { next_ = next_core; }

void Core::TickTock() {
  Task* temp = first_task_;
  if (first_task_ != nullptr) {
    int task_duration = first_task_->GetTaskDuration();
    first_task_->SetTaskDuration(task_duration - 1);
    time_++;
    if (first_task_->GetTaskDuration() == 0) {
      this->RemoveTask(first_task_);
      Message::TASK_REMOVED.PrintMessage(
          {to_string(first_task_->GetTaskId()), "was",
           to_string(time_ - first_task_->GetOriginalTaskDuration())});
    }
  }
}

int Core::GetPendingExecutionTime() const {
  int total = 0;
  Task* temp = first_task_;
  while (temp != nullptr) {
    total = total + temp->GetTaskDuration();
    temp = temp->GetNextTask();
  }
  return total;
}

void Core::AddTask(Task* task) {
  Task* temp = first_task_;

  if (temp == nullptr) {
    first_task_ = task;
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

void Core::RemoveTask(Task* task) {
  core_tasks_->RemoveTask(task);
  completed_tasks_--;
  return;
}

Task* Core::GetFirstTask() const { return first_task_; }

Task* Core::GetTask(std::string task_id) const {
  Task* temp = first_task_;
  while (temp != nullptr) {
    if (temp->GetTaskId() == stoi(task_id)) {
      return temp;
    }
    temp = temp->GetNextTask();
  }
  return nullptr;
}

int Core::GetAssignedTasksNumber() const { return assigned_tasks_; }

int Core::GetCompletedTasksNumber() const { return completed_tasks_; }
