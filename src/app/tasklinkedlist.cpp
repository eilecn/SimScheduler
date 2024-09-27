#include "tasklinkedlist.h"

#include <iostream>

#include "task.h"

using namespace std;

TaskLinkedList::TaskLinkedList() {
  head_ = nullptr;
  time_ = 0;
  Task* temp = head_;
  int total_time = 0;
  while (temp != nullptr) {
    total_time = total_time + temp->GetTaskDuration();
  }
  execution_time_ = total_time;
  delete temp;
}

TaskLinkedList::~TaskLinkedList() {}

void TaskLinkedList::Add(Task* new_task) {
  if (head_ == nullptr) {
    head_ = new_task;
  } else {
    Task* temp = head_;
    while (temp->GetNextTask() != nullptr) {
      cout << "hi" << endl;
      temp = temp->GetNextTask();
    }
    temp->SetNextTask(new_task);
  }
}

void TaskLinkedList::Remove(Task* task_to_delete) {
  if (head_ == nullptr || task_to_delete == nullptr) {
    return;
  }

  if (head_->GetTaskId() == task_to_delete->GetTaskId()) {
    Task* temp = head_;
    head_ = head_->GetNextTask();
    delete temp;
    return;
  }

  Task* current = head_;
  Task* previous = nullptr;

  cout << "hi" << endl;

  while (current != nullptr &&
         current->GetTaskId() != task_to_delete->GetTaskId()) {
    previous = current;
    current = current->GetNextTask();
  }

  cout << "hi" << endl;

  if (current == nullptr) {
    return;
  }

  if (previous != nullptr) {
    previous->SetNextTask(current->GetNextTask());
  }
  delete current;
}

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

void TaskLinkedList::TickTock(int time) {
  time_ = time_ + time;
  Task* temp = head_;
  while (temp != nullptr && time > 0) {
    if (time > temp->GetTaskDuration()) {
      time - temp->GetTaskDuration();
      Remove(temp);
      temp = temp->GetNextTask();
    } else if (time < temp->GetTaskDuration()) {
      temp->SetTaskDuration(temp->GetTaskDuration() - time);
      time = time - temp->GetTaskDuration();
      break;
    } else {
      Remove(temp);
      break;
    }
  }
}
