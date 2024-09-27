#include "app.hpp"

#include <iostream>

#include "core.h"
#include "corelinkedlist.h"
#include "fifo.h"
#include "message.hpp"
#include "priority.h"
#include "scheduler.h"
#include "task.h"
#include "tasklinkedlist.h"
#include "utils.hpp"

using namespace std;

/*
*****************************
  This is where you start!
  However, make sure you do not not write all your code in a single file!
*****************************
*/

App::App() {
  scheduler_exists_ = 0;
  core_id_ = 0;
  system_time_ = 0;
  task_id_ = 0;
}

App::~App() {}

void App::TickTock(const std::string &num_ticktock) {

}

void App::AddScheduler() {
  if (scheduler_exists_ == 0) {
    scheduler_ = new Scheduler();
    scheduler_exists_ = 1;
    Message::SCHEDULER_ADDED.PrintMessage();
  } else {
    Message::ERROR_SECOND_SCHEDULER.PrintMessage();
  }
}

void App::RemoveScheduler() {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else {
    delete scheduler_;
    scheduler_exists_ = 0;
    return;
  }
}

void App::AddCore(const std::string &core_type) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }
  core_type_ = Utils::GetLowercase(core_type);
  if (core_id_ == 0) {
    core_linked_list_ = CoreLinkedList();
  }
  if (core_type_ == "fifo") {
    Fifo *new_fifo_core_ = new Fifo(to_string(core_id_));
    core_linked_list_.Add(new_fifo_core_);
    Message::CORE_ADDED.PrintMessage({core_type_, to_string(core_id_)});
    core_id_++;
    return;
  } else if (core_type_ == "priority") {
    Priority *new_priority_core_ = new Priority(to_string(core_id_));
    core_linked_list_.Add(new_priority_core_);
    Message::CORE_ADDED.PrintMessage({core_type_, to_string(core_id_)});
    core_id_++;
    return;
  } else {
    Message::ERROR_CORE_TYPE.PrintMessage();
    return;
  }
}

void App::RemoveCore(const std::string &core_id) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else if (core_linked_list_.GetCore(core_id) == nullptr) {
    Message::ERROR_NO_CORE.PrintMessage({core_id});
    return;
  } else {
    Core *core_to_delete = core_linked_list_.GetCore(core_id);
    core_linked_list_.Remove(core_to_delete);
    return;
  }
}

void App::AddTask(const std::string &task_time, const std::string &priority) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }

  if (task_id_ == 0) {
    task_linked_list_ = TaskLinkedList();
  }

  Task *new_task = new Task(to_string(task_id_), task_time, priority);
  task_linked_list_.Add(new_task);
  Message::TASK_ADDED.PrintMessage({to_string(task_id_), task_time, priority});
  task_id_++;
  return;
}

void App::RemoveTask(const std::string &task_id) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }

  Core *head_core = core_linked_list_.GetHead();
  if (head_core == nullptr) {
    Message::ERROR_NO_CORES.PrintMessage();
    return;
  }
  Task *head_task = task_linked_list_.GetHead();
  while (head_core != nullptr) {
    while (head_task != nullptr) {
      if (head_task->GetTaskId() == stoi(task_id)) {
        task_linked_list_.Remove(head_task);
        return;
      }
      head_task = head_task->GetNextTask();
    }
    head_core = head_core->GetNextCore();
  }

  if (head_core == nullptr) {
    Message::ERROR_NO_TASK.PrintMessage({task_id});
    return;
  }
}

void App::ShowCore(const std::string &core_id) const {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else if (core_linked_list_.GetCore(core_id) == nullptr) {
    Message::ERROR_NO_CORE.PrintMessage({core_id});
    return;
  } else {
    Core *core_to_show = core_linked_list_.GetCore(core_id);
    // Message::SHOW_CORE.PrintMessage({});
    return;
  }
}

void App::ShowTask(const std::string &task_id) const {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else if (task_linked_list_.GetTask(task_id) == nullptr) {
    Message::ERROR_NO_TASK.PrintMessage({task_id});
    return;
  } else {
    Task *task_to_show = task_linked_list_.GetTask(task_id);
    // Message::SHOW_TASK.PrintMessage({});
    return;
  }
}
