#ifndef APP_H
#define APP_H

#include <string>

#include "corelinkedlist.h"
#include "fifo.h"
#include "priority.h"
#include "scheduler.h"
#include "tasklinkedlist.h"

/*
*****************************
  This is where you start!
  However, make sure you do not not write all your code in a single file!
*****************************
*/

class App {
 private:
  bool scheduler_exists_;
  Scheduler *scheduler_;
  int core_id_;
  int system_time_;
  int task_id_;

 public:
  App(void);
  ~App(void);
  void AddScheduler(void);
  void TickTock(const std::string &num_ticktock);
  void RemoveScheduler(void);
  void AddCore(const std::string &core_type);
  void AddTask(const std::string &consult_time, const std::string &priority);
  void RemoveTask(const std::string &task_id);
  void RemoveCore(const std::string &core_id);
  void ShowTask(const std::string &task_id) const;
  void ShowCore(const std::string &core_id) const;
};

#endif  // APP_H
