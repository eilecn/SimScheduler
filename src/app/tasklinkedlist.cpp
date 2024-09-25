#include "tasklinkedlist.h"

TaskLinkedList::TaskLinkedList() { head = nullptr; }

TaskLinkedList::~TaskLinkedList() {}

void TaskLinkedList::Add(Task* new_core) {
  if (head == nullptr) {
    head = new_core;
  } else {
    Task* temp = head;
    while (temp->GetNextTask() != nullptr) {
      temp = temp->GetNextTask();
    }
    temp->SetNextTask(new_core);
  }
}

void TaskLinkedList::Remove(Task* task_to_delete) {
  if (head == nullptr || task_to_delete == nullptr) {
    return;
  }

  if (head->GetTaskId() == task_to_delete->GetTaskId()) {
    Task* temp = head;
    head = head->GetNextTask();
    delete temp;
    return;
  }

  Task* current = head;
  Task* previous = nullptr;

  while (current != nullptr &&
         current->GetTaskId() != task_to_delete->GetTaskId()) {
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
}

Task* TaskLinkedList::GetTask(std::string task_id) const {
  Task* temp = head;
  while (temp != nullptr) {
    if (temp->GetTaskId() == stoi(task_id)) {
      return temp;
    }
    temp = temp->GetNextTask();
  }
  return nullptr;
}
