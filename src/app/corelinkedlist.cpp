#include "corelinkedlist.h"

#include <iostream>

#include "core.h"

using namespace std;

CoreLinkedList::CoreLinkedList() { head_ = nullptr; core_tasks_ = nullptr;}

CoreLinkedList::~CoreLinkedList() {}

void CoreLinkedList::Add(Core* new_core) {
  if (head_ == nullptr) {
    head_ = new_core;
  } else {
    Core* temp = head_;
    while (temp->GetNextCore() != nullptr) {
      temp = temp->GetNextCore();
    }
    temp->SetNextCore(new_core);
  }
}

void CoreLinkedList::Remove(Core* core_to_delete) {
  if (head_ == nullptr || core_to_delete == nullptr) {
    return;
  }

  if (head_->GetCoreId() == core_to_delete->GetCoreId()) {
    Core* temp = head_;
    head_ = head_->GetNextCore();
    delete temp;
    return;
  }

  Core* current = head_;
  Core* previous = nullptr;

  while (current != nullptr &&
         current->GetCoreId() != core_to_delete->GetCoreId()) {
    previous = current;
    current = current->GetNextCore();
  }

  if (current == nullptr) {
    return;
  }

  if (previous != nullptr) {
    previous->SetNextCore(current->GetNextCore());
  }
  delete current;
}

Core* CoreLinkedList::GetCore(std::string core_id) const {
  Core* temp = head_;
  while (temp != nullptr) {
    if (temp->GetCoreId() == stoi(core_id)) {
      return temp;
    }
    temp = temp->GetNextCore();
  }
  return nullptr;
}

Core* CoreLinkedList::GetHead() const {
  return head_;
}
