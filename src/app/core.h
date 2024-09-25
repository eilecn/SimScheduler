#ifndef CORE_H
#define CORE_H
#include <string>

#include "task.h"

class Core {
 public:
  Core();
  Core(std::string core_id);
  ~Core();
  int GetCoreId() const;
  Core* GetNextCore() const;
  void SetNextCore(Core* next_core);

 private:
  int core_id_;
  Core* next;
};

#endif