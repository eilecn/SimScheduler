#include "tasklinkedlist.h"

#include <iostream>

#include "task.h"
#include "message.hpp"

using namespace std;

TaskLinkedList::TaskLinkedList() {
  head_ = nullptr;
  Task* temp = head_;
  int total_time = 0;
  while (temp != nullptr) {
    total_time = total_time + temp->GetTaskDuration();
  }
  execution_time_ = total_time;
  delete temp;
}

TaskLinkedList::~TaskLinkedList() {}

Task* TaskLinkedList::GetTask(std::string task_id) const {
  Task* temp = head_;
  while (temp != nullptr) {
    if (temp->GetTaskId() == stoi(task_id)) {
      return temp;
    }
    temp = temp->GetNextTask();
  }
  return nullptr;
}

int TaskLinkedList::GetExecutionTime() const { return execution_time_; }

Task* TaskLinkedList::GetHead() const { return head_; }

void TaskLinkedList::RemoveTask(Task* task_to_remove) {
  if (head_ == nullptr || task_to_remove == nullptr) {
    return;
  }

  if (head_->GetTaskId() == task_to_remove->GetTaskId()) {
    Task* temp = head_;
    head_ = head_->GetNextTask();
    delete temp;
    return;
  }

  Task* current = head_;
  Task* previous = nullptr;

  while (current != nullptr &&
         current->GetTaskId() != task_to_remove->GetTaskId()) {
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
  return;
}
