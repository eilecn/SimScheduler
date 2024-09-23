#include "app.hpp"

#include <iostream>

#include "message.hpp"
#include "utils.hpp"
#include "scheduler.h"
#include "core.h"

using namespace std;

/*
*****************************
  This is where you start!
  However, make sure you do not not write all your code in a single file!
*****************************
*/

App::App() {
  SchedulerExists = 0;
}

App::~App() {}

void App::TickTock(const std::string &num_ticktock) {}

void App::AddScheduler() {
  if (SchedulerExists == 0) {
    scheduler_ = new Scheduler();
    SchedulerExists = 1;
    Message::SCHEDULER_ADDED.PrintMessage();
  } else {
    Message::ERROR_SECOND_SCHEDULER.PrintMessage();
  }
  
}

void App::RemoveScheduler() {
  if (SchedulerExists = 0) {
    Message::ERROR_NO_SCHEDULERS.PrintMessage();
    return;
  } else {
    delete scheduler_;
    SchedulerExists = 0;
    Message::SCHEDULER_REMOVED.PrintMessage();
    return;
  }
}

void App::AddCore(const std::string &core_type) {}

void App::RemoveCore(const std::string &core_id) {}

void App::AddTask(const std::string &task_time, const std::string &priority) {}

void App::RemoveTask(const std::string &task_id) {}

void App::ShowCore(const std::string &core_id) const {}

void App::ShowTask(const std::string &task_id) const {}
