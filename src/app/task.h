#ifndef NODE_H
#define NODE_H

#include "core.h"
#include <string>

class Task
{
public:
    Task(const std::string id, const std::string duration, const std::string priority);
    ~Task();

private:
 int id_;
 int duration_;
 int priority_;
 Task *next;
};

#endif
