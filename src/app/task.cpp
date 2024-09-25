#include <iostream>
#include "task.h"
#include <string>

using namespace std;

Task::Task(const std::string id, const std::string duration, const std::string priority)
{
  id_ = stoi(id);
  duration_ = stoi(duration);
  priority_ = stoi(priority);
}

Task::Task() {
  
}

Task::~Task()
{

}