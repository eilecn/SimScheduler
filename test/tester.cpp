#include <algorithm>
#include <cctype>
#include <cstring>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "app/launcher.hpp"
#include "app/utils.hpp"

using namespace std;

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  DO NOT MODIFY EXISTING METHODS. You may add additional test cases if you wish.
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

enum TestResult { TEST_RESULT_PASS, TEST_RESULT_FAIL };

#include <sstream>
#include <string>
#include <vector>

#define RUN_COMMAND(command_with_args)                           \
  cout << app.GetCommandPrefix() << command_with_args << "\n\r"; \
  app.ProcessCommand(command_with_args);

#define RUN_COMMAND_WITH_OPTIONS(command_with_args, options_str)              \
  {                                                                           \
    std::vector<std::string> _options = Utils::SplitString(options_str, ";"); \
    cout << app.GetCommandPrefix() << command_with_args << "\n\r";            \
    app.ProcessCommand(command_with_args, _options);                          \
  }

#define __FILENAME__ \
  (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define EXPECT_CONTAINS(expected)                                              \
  if (still_capturing_cout) {                                                  \
    still_capturing_cout = false;                                              \
    output = replaceNewlineWithCRLF(buffer.str());                             \
    std::cout.rdbuf(old);                                                      \
    std::cout << output << "\n\r";                                             \
  }                                                                            \
  if (output.find(expected) == std::string::npos) {                            \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__            \
         << " on line " << __LINE__ << ":\n\r" << "  Expected '" << expected   \
         << "' in the output, but it was not found." << "\n\r" << "\n\r"       \
         << "----------------------------------------------------------------" \
            "------------"                                                     \
         << "\n\r" << "\n\r";                                                  \
    return TEST_RESULT_FAIL;                                                   \
  }

#define EXPECT_DOES_NOT_CONTAINS(expected, ignore_case)                      \
  output = replaceNewlineWithCRLF(buffer.str());                             \
  if (Utils::Contains(output, expected, ignore_case)) {                      \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__          \
         << " on line " << __LINE__ << ":\n\r" << "\tExpected '" << expected \
         << "' to NOT be in the output, but it was." << "\n\r" << "\n\r";    \
    return TEST_RESULT_FAIL;                                                 \
  }

std::string replaceNewlineWithCRLF(const std::string &input) {
  std::string replacedStr;
  for (char ch : input) {
    if (ch == '\n') {
      replacedStr += "\n\r";
    } else {
      replacedStr += ch;
    }
  }
  return replacedStr;
}

int main(int argc, char *argv[]) {
  Launcher app;
  string output = "";
  bool still_capturing_cout = true;
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  int test_number = std::stoi(argv[1]);
  switch (test_number) {
    case 1:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler");
      EXPECT_CONTAINS("Removed scheduler");
      break;

    case 2:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler");
      EXPECT_CONTAINS("Cannot add another scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Core 0 is currently assigned 0 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      break;

    case 3:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("remove-core 2");
      RUN_COMMAND("remove-core 1");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("remove-core 3");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 1.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 2.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 3.");
      EXPECT_CONTAINS("Removed core 2.");
      EXPECT_CONTAINS("Removed core 1.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Cannot perform that operation without first removing core(s).");
      EXPECT_CONTAINS("Removed core 3.");
      EXPECT_CONTAINS("Removed scheduler.");
      break;

    case 4:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-core 1");
      RUN_COMMAND("remove-core 2");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 1.");
      EXPECT_CONTAINS("Core 0 is currently assigned 0 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 0 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed core 1.");
      EXPECT_CONTAINS("Cannot perform that operation without a core.");
      EXPECT_CONTAINS("Removed scheduler.");
      break;

    case 5:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-task 5 10");
      RUN_COMMAND("add-task 5 8");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("remove-task 1");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("ticktock 5");
      RUN_COMMAND("add-task 5 10");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("add-task 2 10");
      RUN_COMMAND("add-task 2 1");
      RUN_COMMAND("add-task 10 1");
      RUN_COMMAND("add-task 20 1");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("show-core 2");
      RUN_COMMAND("ticktock 100");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-core 1");
      RUN_COMMAND("remove-core 2");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.")
      EXPECT_CONTAINS("Added core of type 'priority' with ID 0.")
      EXPECT_CONTAINS("Added core of type 'priority' with ID 1.")
      EXPECT_CONTAINS("Added core of type 'priority' with ID 2.")
      EXPECT_CONTAINS("Added task with ID 0, task time of 5, and priority of 10.")
      EXPECT_CONTAINS("Added task with ID 1, task time of 5, and priority of 8.")
      EXPECT_CONTAINS("SimScheduler clock is now 2.")
      EXPECT_CONTAINS("Task 1 is currently being executed.")
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).")
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.")
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 0.")
      EXPECT_CONTAINS("SimScheduler clock is now 7.")
      EXPECT_CONTAINS("Added task with ID 2, task time of 5, and priority of 10.")
      EXPECT_CONTAINS("Added task with ID 3, task time of 10, and priority of 10.")
      EXPECT_CONTAINS("Added task with ID 4, task time of 2, and priority of 10.")
      EXPECT_CONTAINS("Added task with ID 5, task time of 2, and priority of 1.")
      EXPECT_CONTAINS("Added task with ID 6, task time of 10, and priority of 1.")
      EXPECT_CONTAINS("Added task with ID 7, task time of 20, and priority of 1.")
      EXPECT_CONTAINS("Removed task 5 which was executed after waiting 0.")
      EXPECT_CONTAINS("Removed task 3 which was executed after waiting 0.")
      EXPECT_CONTAINS("SimScheduler clock is now 17.")
      EXPECT_CONTAINS("Core 0 is currently assigned 2 task(s) and has completed 1 task(s).")
      EXPECT_CONTAINS("Core 1 is currently assigned 0 task(s) and has completed 2 task(s).")
      EXPECT_CONTAINS("Core 2 is currently assigned 2 task(s) and has completed 1 task(s).")
      EXPECT_CONTAINS("Removed task 6 which was executed after waiting 2.")
      EXPECT_CONTAINS("Removed task 4 which was executed after waiting 12.")
      EXPECT_CONTAINS("Removed task 7 which was executed after waiting 0.")
      EXPECT_CONTAINS("Removed task 2 which was executed after waiting 20.")
      EXPECT_CONTAINS("SimScheduler clock is now 117.")
      EXPECT_CONTAINS("Removed core 0.")
      EXPECT_CONTAINS("Removed core 1.")
      EXPECT_CONTAINS("Removed core 2.")
      EXPECT_CONTAINS("Removed scheduler.")
      break;

    case 6:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-task 10 5");
      RUN_COMMAND("add-task 2 5");
      RUN_COMMAND("add-task 2 4");
      RUN_COMMAND("add-task 2 3");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 10");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 1.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 5.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 2, and priority of 5.");
      EXPECT_CONTAINS("Added task with ID 2, task time of 2, and priority of 4.");
      EXPECT_CONTAINS("Added task with ID 3, task time of 2, and priority of 3.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 3 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Removed task 3 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 2.");
      EXPECT_CONTAINS("Core 1 is currently assigned 2 task(s) and has completed 1 task(s).");
      EXPECT_CONTAINS("Removed task 2 which was executed after waiting 2.");
      EXPECT_CONTAINS("SimScheduler clock is now 4.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 4.");
      EXPECT_CONTAINS("SimScheduler clock is now 6.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 0 task(s) and has completed 3 task(s).");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 16.");
      break;

    case 7:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-task 5 2");
      RUN_COMMAND("add-task 4 2");
      RUN_COMMAND("add-task 4 1");
      RUN_COMMAND("add-task 5 7");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 8");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 5");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-core 1");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 1.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 5, and priority of 2.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 4, and priority of 2.");
      EXPECT_CONTAINS("Added task with ID 2, task time of 4, and priority of 1.");
      EXPECT_CONTAINS("Added task with ID 3, task time of 5, and priority of 7.");
      EXPECT_CONTAINS("Core 0 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Removed task 2 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 4.");
      EXPECT_CONTAINS("SimScheduler clock is now 8.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 1 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 0 task(s) and has completed 2 task(s).");
      EXPECT_CONTAINS("Removed task 3 which was executed after waiting 5.");
      EXPECT_CONTAINS("SimScheduler clock is now 13.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed core 1.");
      break;

    case 8:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("remove-core 2");
      RUN_COMMAND("show-core 2");
      EXPECT_CONTAINS("Added scheduler.")
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.")
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 1.")
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 2.")
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 3.")
      EXPECT_CONTAINS("Removed core 2.")
      EXPECT_CONTAINS("No core with ID 2.")
      break;

    case 9:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("exit")
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 1.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 2.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 3.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 4.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 5.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 6.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 7.");
      EXPECT_CONTAINS("Cannot add another core.");
      break;

    case 10:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-task 10 5");
      RUN_COMMAND("add-task 2 5");
      RUN_COMMAND("add-task 2 4");
      RUN_COMMAND("add-task 2 3");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("show-core 2");
      RUN_COMMAND("show-core 3");
      RUN_COMMAND("remove-core 3");
      RUN_COMMAND("remove-core 2");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("show-core 2");
      RUN_COMMAND("ticktock 10");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 1.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 2.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 5.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 2, and priority of 5.");
      EXPECT_CONTAINS("Added task with ID 2, task time of 2, and priority of 4.");
      EXPECT_CONTAINS("Added task with ID 3, task time of 2, and priority of 3.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 2 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("No core with ID 3.");
      EXPECT_CONTAINS("No core with ID 3.");
      EXPECT_CONTAINS("Core 2 is currently executing a task.");
      EXPECT_CONTAINS("Removed task 3 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 2 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 2.");
      EXPECT_CONTAINS("Core 1 is currently assigned 1 task(s) and has completed 1 task(s).");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 2.");
      EXPECT_CONTAINS("SimScheduler clock is now 4.");
      EXPECT_CONTAINS("SimScheduler clock is now 6.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 0 task(s) and has completed 2 task(s).");
      EXPECT_CONTAINS("Core 2 is currently assigned 0 task(s) and has completed 1 task(s).");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 16.");
      break;

    case 11:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("show-task 0");
      RUN_COMMAND("show-task 1");
      RUN_COMMAND("show-task 2");
      RUN_COMMAND("remove-task 0");
      RUN_COMMAND("remove-task 1");
      RUN_COMMAND("ticktock 20");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 10.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 10, and priority of 10.");
      EXPECT_CONTAINS("Task 0, time arrival 0, task time 10, pending execution time 10, priority 10.");
      EXPECT_CONTAINS("Task 1, time arrival 0, task time 10, pending execution time 10, priority 10.");
      EXPECT_CONTAINS("No task with ID 2.");
      EXPECT_CONTAINS("Task 0 is currently being executed.");
      EXPECT_CONTAINS("Removed task 1 which was not executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 20.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      break;

    case 12:  // 
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("ticktock 5");
      RUN_COMMAND("add-task 9 9  ");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-task 0");
      RUN_COMMAND("show-task 1");
      RUN_COMMAND("ticktock 2");
      RUN_COMMAND("show-task 0");
      RUN_COMMAND("show-task 1");
      RUN_COMMAND("ticktock 20");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 10.");
      EXPECT_CONTAINS("SimScheduler clock is now 5.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 9, and priority of 9.");
      EXPECT_CONTAINS("Core 0 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Task 0, time arrival 0, task time 10, pending execution time 5, priority 10.");
      EXPECT_CONTAINS("Task 1, time arrival 5, task time 9, pending execution time 9, priority 9.");
      EXPECT_CONTAINS("SimScheduler clock is now 7.");
      EXPECT_CONTAINS("Task 0, time arrival 0, task time 10, pending execution time 3, priority 10.");
      EXPECT_CONTAINS("Task 1, time arrival 5, task time 9, pending execution time 9, priority 9.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 5.");
      EXPECT_CONTAINS("SimScheduler clock is now 27.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      break;

    case 13:  // 
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Cannot perform that operation without a scheduler.");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("SimScheduler clock is now 10.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 14:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("remove-task 0");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Cannot perform that operation without a core.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 10.");
      EXPECT_CONTAINS("Task 0 is currently being executed.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 10.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 15:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("show-core 8");
      RUN_COMMAND("show-core 7");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 1.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 2.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 3.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 4.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 5.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 6.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 7.");
      EXPECT_CONTAINS("Cannot add another core.");
      EXPECT_CONTAINS("No core with ID 8.");
      EXPECT_CONTAINS("Core 7 is currently assigned 0 task(s) and has completed 0 task(s).");
      break;

    case 16:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("add-task 10 9");
      RUN_COMMAND("ticktock 20");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("SimScheduler clock is now 10.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 10.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 10, and priority of 9.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 10.");
      EXPECT_CONTAINS("SimScheduler clock is now 30.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 17:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("add-task 10 9");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("remove-core 1");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 1.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 10.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 10, and priority of 9.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 10.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Cannot perform that operation without first removing core(s).");
      EXPECT_CONTAINS("Removed core 1.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 18:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-task 10 10");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("add-task 2 10");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("add-task 2 9");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 4");
      RUN_COMMAND("ticktock 6");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-core 1");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 1.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 10.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Added task with ID 1, task time of 2, and priority of 10.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Added task with ID 2, task time of 2, and priority of 9.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 2 which was executed after waiting 2.");
      EXPECT_CONTAINS("SimScheduler clock is now 4.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 10.");
      EXPECT_CONTAINS("Core 0 is currently assigned 0 task(s) and has completed 1 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 0 task(s) and has completed 2 task(s).");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed core 1.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 19:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-task 10 2 ");
      RUN_COMMAND("add-task 10 1");
      RUN_COMMAND("ticktock 20");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 0.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 2.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 10, and priority of 1.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 10.");
      EXPECT_CONTAINS("SimScheduler clock is now 20.");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 20:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("add-core fifo");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("add-task 10 4");
      RUN_COMMAND("add-task 10 3");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("add-task 10 2");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("add-task 10 1");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("ticktock 10");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("show-core 1");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-core 1");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("SimScheduler clock is now 10.");
      EXPECT_CONTAINS("Added core of type 'fifo' with ID 0.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 1.");
      EXPECT_CONTAINS("Core 0 is currently assigned 0 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 4.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 10, and priority of 3.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Added task with ID 2, task time of 10, and priority of 2.");
      EXPECT_CONTAINS("Core 0 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Added task with ID 3, task time of 10, and priority of 1.");
      EXPECT_CONTAINS("Core 1 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 3 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 20.");
      EXPECT_CONTAINS("Removed task 2 which was executed after waiting 10.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 10.");
      EXPECT_CONTAINS("SimScheduler clock is now 30.");
      EXPECT_CONTAINS("Core 0 is currently assigned 0 task(s) and has completed 2 task(s).");
      EXPECT_CONTAINS("Core 1 is currently assigned 0 task(s) and has completed 2 task(s).");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed core 1.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 21:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-task 10 2");
      RUN_COMMAND("ticktock 5");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("add-task 10 1");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("ticktock 5");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("ticktock 5");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("ticktock 5");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 0.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 2.");
      EXPECT_CONTAINS("SimScheduler clock is now 5.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Added task with ID 1, task time of 10, and priority of 1.");
      EXPECT_CONTAINS("Core 0 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("SimScheduler clock is now 10.");
      EXPECT_CONTAINS("Core 0 is currently assigned 2 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 0.");
      EXPECT_CONTAINS("SimScheduler clock is now 15.");
      EXPECT_CONTAINS("Core 0 is currently assigned 1 task(s) and has completed 1 task(s).");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 10.");
      EXPECT_CONTAINS("SimScheduler clock is now 20.");
      EXPECT_CONTAINS("Core 0 is currently assigned 0 task(s) and has completed 2 task(s).");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    case 22:
      RUN_COMMAND("add-scheduler");
      RUN_COMMAND("add-core priority");
      RUN_COMMAND("add-task 10 4");
      RUN_COMMAND("add-task 10 3");
      RUN_COMMAND("add-task 10 2");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("add-task 10 1");
      RUN_COMMAND("ticktock 40");
      RUN_COMMAND("show-core 0");
      RUN_COMMAND("remove-core 0");
      RUN_COMMAND("remove-scheduler");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Added scheduler.");
      EXPECT_CONTAINS("Added core of type 'priority' with ID 0.");
      EXPECT_CONTAINS("Added task with ID 0, task time of 10, and priority of 4.");
      EXPECT_CONTAINS("Added task with ID 1, task time of 10, and priority of 3.");
      EXPECT_CONTAINS("Added task with ID 2, task time of 10, and priority of 2.");
      EXPECT_CONTAINS("Core 0 is currently assigned 3 task(s) and has completed 0 task(s).");
      EXPECT_CONTAINS("Added task with ID 3, task time of 10, and priority of 1.");
      EXPECT_CONTAINS("Removed task 3 which was executed after waiting 0.");
      EXPECT_CONTAINS("Removed task 2 which was executed after waiting 10.");
      EXPECT_CONTAINS("Removed task 1 which was executed after waiting 20.");
      EXPECT_CONTAINS("Removed task 0 which was executed after waiting 30.");
      EXPECT_CONTAINS("SimScheduler clock is now 40.");
      EXPECT_CONTAINS("Core 0 is currently assigned 0 task(s) and has completed 4 task(s).");
      EXPECT_CONTAINS("Removed core 0.");
      EXPECT_CONTAINS("Removed scheduler.");
      EXPECT_CONTAINS("Program ended.");
      break;

    default:
      cerr << "Test case not found: #" << test_number << endl;
      return TEST_RESULT_FAIL;
  }

  cerr << "PASSED Test " << test_number << "." << "\n\r" << "\n\r"
       << "--------------------------------------------------------------------"
          "--------"
       << "\n\r" << "\n\r";
  return TEST_RESULT_PASS;
}
