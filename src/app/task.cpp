#include "task.h"

#include <iostream>
#include <string>

#include "message.hpp"

using namespace std;

Task::Task(const std::string id, const std::string time,
           const std::string priority, const std::string arrival_time) {
  task_id_ = stoi(id);
  duration_ = stoi(time);
  original_duration_ = stoi(time);
  priority_ = stoi(priority);
  next_ = nullptr;
  time_in_system_ = 0;
  arrival_time_ = stoi(arrival_time);
}

Task::Task() {}

Task::~Task() {}

int Task::GetTaskId() const { return task_id_; }

int Task::GetTaskDuration() const { return duration_; }

Task* Task::GetNextTask() const { return next_; }

void Task::SetNextTask(Task* next_task) { next_ = next_task; }

void Task::SetTaskDuration(int duration_to_set) { duration_ = duration_to_set; }

int Task::GetOriginalTaskDuration() const { return original_duration_; }

int Task::GetPriority() const { return priority_; }

void Task::SubractOneTick() {
  if (duration_ > 0) {
    duration_ = duration_ - 1;
  }
}

void Task::IncrementTimeInSystem() { time_in_system_ += 1; }

int Task::GetTimeInSystem() const { return time_in_system_; }

int Task::GetArrivalTime() const { return arrival_time_; }
