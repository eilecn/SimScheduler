#ifndef FIFO_H
#define FIFO_H

#include "core.h"
#include <string>

class Fifo : public Core {
 public:
  Fifo();
  Fifo(std::string core_id);
  ~Fifo();

 private:

};

#endif
