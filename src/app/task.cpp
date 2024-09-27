#include "task.h"

#include <iostream>
#include "message.hpp"
#include <string>

using namespace std;

Task::Task(const std::string id, const std::string time,
           const std::string priority) {
  task_id_ = stoi(id);
  duration_ = stoi(time);
  priority_ = stoi(priority);
  next_ = nullptr;
}

Task::Task() {}

Task::~Task() {
  Message::TASK_REMOVED.PrintMessage({to_string(task_id_), "hi", "hi"});
}

int Task::GetTaskId() const { return task_id_; }

int Task::GetTaskDuration() const { return duration_; }

Task* Task::GetNextTask() const { return next_; }

void Task::SetNextTask(Task* next_task) { next_ = next_task; }

void Task::SetTaskDuration(int duration_to_set) {
  duration_ = duration_to_set;
}