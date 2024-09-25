#include "corelinkedlist.h"

#include <iostream>

#include "core.h"

using namespace std;

CoreLinkedList::CoreLinkedList() { head = nullptr; }

CoreLinkedList::~CoreLinkedList() {}

void CoreLinkedList::Add(Core* new_core) {
  if (head == nullptr) {
    head = new_core;
  } else {
    Core* temp = head;
    while (temp->GetNextCore() != nullptr) {
      temp = temp->GetNextCore();
    }
    temp->SetNextCore(new_core);
  }
}

void CoreLinkedList::Remove(Core* core_to_delete) {
  if (head == nullptr || core_to_delete == nullptr) {
    return;
  }

  if (head->GetCoreId() == core_to_delete->GetCoreId()) {
    Core* temp = head;
    head = head->GetNextCore();
    delete temp;
    return;
  }

  Core* current = head;
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
  Core* temp = head;
  while (temp != nullptr) {
    if (temp->GetCoreId() == stoi(core_id)) {
      return temp;
    }
    temp = temp->GetNextCore();
  }
  return nullptr;
}
