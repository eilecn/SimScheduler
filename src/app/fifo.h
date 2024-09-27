#ifndef FIFO_H
#define FIFO_H
#include <string>

#include "core.h"

class Fifo : public Core {
 public:
  Fifo();
  Fifo(std::string core_id);
  ~Fifo();

 private:
};

#endif
