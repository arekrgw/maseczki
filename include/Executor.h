#pragma once
#include <string>

class Executor
{
private:
  bool initialized = false;
  bool commandExecuted = false;
  std::string successCommand;
  std::string failureCommand;

public:
  Executor() = default;
  enum CommandType
  {
    FAILURE = 1,
    SUCCESS
  };
  void resetExecutor();
  bool executeCommand(CommandType type);
  Executor(int argc, char **argv);
};