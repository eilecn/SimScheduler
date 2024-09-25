#include "corelinkedlist.h"
#include "core.h"

CoreLinkedList::CoreLinkedList() { head = nullptr; }

CoreLinkedList::~CoreLinkedList() {}

void CoreLinkedList::Add(Core* newCore) {
  if (head == nullptr) {
    head = newCore;
  } else {
    Core* temp = head;
    while (temp->GetNextCore() != nullptr) {
      temp = temp->GetNextCore();
    }
    temp->SetNextCore(newCore);
  }
}