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
  system_time_ = system_time_ + stoi(num_ticktock);
  for (int i = 0; i < stoi(num_ticktock); i++) {
    // ticktock scheduler by 1 tick
  }
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
  cout << scheduler_->GetNumberOfCores() << endl;
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else if (scheduler_->GetNumberOfCores() > 0) {
    Message::ERROR_CORES.PrintMessage();
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
  std::string core_type_to_add = Utils::GetLowercase(core_type);

  if (core_type_to_add == "fifo") {
    Fifo *new_fifo_core = new Fifo(to_string(core_id_));
    scheduler_->AddCore(new_fifo_core);
    Message::CORE_ADDED.PrintMessage({core_type_to_add, to_string(core_id_)});
    core_id_++;
    return;
  } else if (core_type_to_add == "priority") {
    Priority *new_priority_core = new Priority(to_string(core_id_));
    scheduler_->AddCore(new_priority_core);
    Message::CORE_ADDED.PrintMessage({core_type_to_add, to_string(core_id_)});
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
  } else if (scheduler_->GetNumberOfCores() == 0) {
    Message::ERROR_NO_CORES.PrintMessage();
    return;
  } else if (scheduler_->GetCore(core_id) == nullptr) {
    Message::ERROR_NO_CORE.PrintMessage({core_id});
    return;
  } else {
    Core *core_to_delete = scheduler_->GetCore(core_id);
    scheduler_->RemoveCore(core_to_delete);
    return;
  }
}

void App::AddTask(const std::string &task_time, const std::string &priority) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }
  Task *new_task = new Task(to_string(task_id_), task_time, priority);
  int shortest_time = scheduler_->GetCoreHead()->GetPendingExecutionTime();
  Core *shortest_execution_core = scheduler_->GetCoreHead();
  Core *temp = scheduler_->GetCoreHead();
  while (temp != nullptr) {
    if (temp->GetPendingExecutionTime() < shortest_time) {
      shortest_time = temp->GetPendingExecutionTime();
      shortest_execution_core = temp;
    }
    temp = temp->GetNextCore();
  }
  temp->AddTask(new_task);
  delete temp;
  Message::TASK_ADDED.PrintMessage({to_string(task_id_), task_time, priority});
  task_id_++;
  return;
}

void App::RemoveTask(const std::string &task_id) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }

  Core *head_core = scheduler_->GetCoreHead();
  if (head_core == nullptr) {
    Message::ERROR_NO_CORES.PrintMessage();
    return;
  } else {
    while (head_core != nullptr) {
      Task *temp = head_core->GetFirstTask();
      while (temp != nullptr) {
        if (temp->GetTaskId() == stoi(task_id)) {
          head_core->RemoveTask(head_core->GetTask(task_id));
          return;
        }
      }
    }
  }
}

void App::ShowCore(const std::string &core_id) const {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else if (scheduler_->GetCore(core_id) == nullptr) {
    Message::ERROR_NO_CORE.PrintMessage({core_id});
    return;
  } else {
    Core *core_to_show = scheduler_->GetCore(core_id);
    Message::SHOW_CORE.PrintMessage(
        {core_id, to_string(core_to_show->GetAssignedTasksNumber()),
         to_string(core_to_show->GetCompletedTasksNumber())});
    return;
  }
}

void App::ShowTask(const std::string &task_id) const {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
    // } else if (task_linked_list_.GetTask(task_id) == nullptr) {
    //   Message::ERROR_NO_TASK.PrintMessage({task_id});
    //   return;
    // } else {
    //   Task *task_to_show = task_linked_list_.GetTask(task_id);
    //   // Message::SHOW_TASK.PrintMessage({});
    //   return;
    // }
  }
}
