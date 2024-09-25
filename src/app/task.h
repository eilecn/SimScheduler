#ifndef NODE_H
#define NODE_H

#include <string>

#include "core.h"

class Task {
 public:
  Task();
  Task(const std::string id, const std::string duration,
       const std::string priority);
  ~Task();

 private:
  int id_;
  int duration_;
  int priority_;
  Task *next;
};

#endif
