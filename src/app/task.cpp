#include "task.h"

#include <iostream>
#include <string>

using namespace std;

Task::Task(const std::string id, const std::string time,
           const std::string priority) {
  task_id_ = stoi(id);
  duration_ = stoi(time);
  priority_ = stoi(priority);
  next = nullptr;
}

Task::Task() {}

Task::~Task() {}

int Task::GetTaskId() const { return task_id_; }

Task* Task::GetNextTask() const { return next; }

void Task::SetNextTask(Task* next_task) { next = next_task; }