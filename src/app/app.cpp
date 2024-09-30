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
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }
  system_time_ = system_time_ + stoi(num_ticktock);
  for (int i = 0; i < stoi(num_ticktock); i++) {
    scheduler_->TickTock();
  }
  Message::SIMSCHEDULER_CLOCK.PrintMessage({to_string(system_time_)});
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
  if (scheduler_exists_ == 0 || scheduler_ == nullptr) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }
  if (scheduler_->GetNumberOfCores() > 0) {
    Message::ERROR_CORES.PrintMessage();
    return;
  } else {
    delete scheduler_;
    scheduler_exists_ = 0;
    core_id_ = 0;
    system_time_ = 0;
    return;
  }
}

void App::AddCore(const std::string &core_type) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }
  std::string core_type_to_add = Utils::GetLowercase(core_type);

  if (scheduler_->GetNumberOfCores() >= 8) {
    Message::ERROR_MAX_CORES.PrintMessage();
    return;
  }

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
  } else if (scheduler_->GetCore(core_id)->GetPendingExecutionTime() > 0) {
    Message::ERROR_CORE_NOT_FREE.PrintMessage({core_id});
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
  } else if (scheduler_->GetCoreHead() == nullptr) {
    Message::ERROR_NO_CORES.PrintMessage();
    return;
  }
  Task *new_task = new Task(to_string(task_id_), task_time, priority,
                            to_string(system_time_));
  scheduler_->AddTask(new_task);
  Message::TASK_ADDED.PrintMessage({to_string(task_id_), task_time, priority});
  task_id_++;
  return;
}

void App::RemoveTask(const std::string &task_id) {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  }
  Task *task_to_remove = scheduler_->GetTask(task_id);

  Core *temp = scheduler_->GetCoreHead();

  if (task_to_remove == nullptr) {
    Message::ERROR_NO_TASK.PrintMessage({task_id});
    return;
  }

  while (temp != nullptr) {
    if (temp->GetFirstTask() == task_to_remove) {
      Message::TASK_NOT_REMOVED.PrintMessage({task_id});
      return;
    }
    temp = temp->GetNextCore();
  }
  delete temp;

  Core *core_to_remove_task = scheduler_->GetTaskCore(task_id);
  core_to_remove_task->RemoveTask(task_to_remove);
  Message::TASK_REMOVED.PrintMessage(
      {task_id, "was not", to_string(task_to_remove->GetTimeInSystem())});
  return;
}

void App::ShowCore(const std::string &core_id) const {
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
    Core *core_to_show = scheduler_->GetCore(core_id);
    Message::SHOW_CORE.PrintMessage(
        {to_string(stoi(core_id)),
         to_string(core_to_show->GetAssignedTasksNumber()),
         to_string(core_to_show->GetCompletedTasksNumber())});
    return;
  }
}

void App::ShowTask(const std::string &task_id) const {
  if (scheduler_exists_ == 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else if (scheduler_->GetTask(task_id) == nullptr) {
    Message::ERROR_NO_TASK.PrintMessage({task_id});
    return;
  } else {
    Task *task_to_show = scheduler_->GetTask(task_id);
    Message::SHOW_TASK.PrintMessage(
        {task_id, to_string(task_to_show->GetArrivalTime()),
         to_string(task_to_show->GetOriginalTaskDuration()),
         to_string(task_to_show->GetTaskDuration()),
         to_string(task_to_show->GetPriority())});
    return;
  }
}
