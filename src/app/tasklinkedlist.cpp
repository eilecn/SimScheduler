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
