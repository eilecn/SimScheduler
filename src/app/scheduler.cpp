#include "scheduler.h"

#include <iostream>

#include "core.h"
#include "message.hpp"
#include "task.h"
#include "tasklinkedlist.h"

using namespace std;

Scheduler::Scheduler() {
  time_ = 0;
  core_linked_list_ = CoreLinkedList();
}

Scheduler::~Scheduler() { Message::SCHEDULER_REMOVED.PrintMessage(); }

void Scheduler::TickTock() {
  Core* temp = core_linked_list_.GetHead();
  while (temp != nullptr) {
    //ticktock each core
    temp = temp->GetNextCore();
    return;
  }
}

void Scheduler::AddCore(Core* core_to_add) {
  core_linked_list_.Add(core_to_add);
  number_of_cores_++;
  return;
}

void Scheduler::RemoveCore(Core* core_to_remove) {
  core_linked_list_.Remove(core_to_remove);
  number_of_cores_--;
  return;
}

Core* Scheduler::GetCore(std::string core_id_to_get) const {
  Core* current_core = core_linked_list_.GetHead();
  while (current_core != nullptr) {
    if (current_core->GetCoreId() == stoi(core_id_to_get)) {
      return current_core;
    }
    current_core = current_core->GetNextCore();
  }
  return nullptr;
}

Core* Scheduler::GetCoreHead() const { return core_linked_list_.GetHead(); }

int Scheduler::GetNumberOfCores() const {
  int number = 0;
  Core* temp = core_linked_list_.GetHead();
  while (temp != nullptr) {
    number++;
    temp = temp->GetNextCore();
  }
  delete temp;
  return number;
}
