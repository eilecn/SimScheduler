#ifndef PRIORITY_H
#define PRIORITY_H
#include <string>

#include "core.h"

class Priority : public Core {
 public:
  Priority();
  Priority(std::string core_id);
  ~Priority();

 private:
};

#endif
