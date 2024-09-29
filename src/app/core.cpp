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
  pending_execution_time_ = 0;
  assigned_tasks_ = 0;
  completed_tasks_ = 0;
  time_ = 0;
}

Core::Core() {}

Core::~Core() {
  Message::CORE_REMOVED.PrintMessage({to_string(core_id_)});
  delete this->core_tasks_;
}

int Core::GetCoreId() const { return core_id_; }

Core* Core::GetNextCore() const { return next_; }

void Core::SetNextCore(Core* next_core) { next_ = next_core; }

void Core::TickTock() {
  Task* temp = core_tasks_->GetHead();
  while (temp != nullptr) {
    temp->IncrementTimeInSystem();
    temp = temp->GetNextTask();
  }
  temp = core_tasks_->GetHead();
  if (temp != nullptr) {
    temp->Tick();
    time_++;
    if (temp->GetTaskDuration() == 0) {
      Message::TASK_REMOVED.PrintMessage(
          {to_string(temp->GetTaskId()), "was",
           to_string(temp->GetTimeInSystem() -
                     temp->GetOriginalTaskDuration())});
      core_tasks_->SetHead(temp->GetNextTask());
      completed_tasks_++;
      assigned_tasks_--;
      delete temp;
    }
  }
}

int Core::GetPendingExecutionTime() const {
  int total = 0;
  Task* temp = core_tasks_->GetHead();
  while (temp != nullptr) {
    total = total + temp->GetTaskDuration();
    temp = temp->GetNextTask();
  }
  return total;
}

void Core::AddTask(Task* task) { return; }

void Core::RemoveTask(Task* task) {
  Task* temp = core_tasks_->GetHead();
  if (temp == nullptr || task == nullptr) {
    return;
  }

  if (core_tasks_->GetHead()->GetTaskId() == task->GetTaskId()) {
    Task* temp = core_tasks_->GetHead();
    core_tasks_->SetHead(core_tasks_->GetHead()->GetNextTask());
    delete temp;
    return;
  }

  Task* current = core_tasks_->GetHead();
  Task* previous = nullptr;

  while (current != nullptr && current->GetTaskId() != task->GetTaskId()) {
    previous = current;
    current = current->GetNextTask();
  }

  if (current == nullptr) {
    return;
  }

  if (previous != nullptr) {
    previous->SetNextTask(current->GetNextTask());
  }
  delete current;
  completed_tasks_++;
  assigned_tasks_--;
}

Task* Core::GetFirstTask() const { return core_tasks_->GetHead(); }

Task* Core::GetTask(std::string task_id) const {
  Task* temp = core_tasks_->GetHead();
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
