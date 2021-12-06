#include <Executor.h>
#include <iostream>

Executor::Executor(int argc, char **argv)
{
  if (argc < 3)
    return;

  successCommand = argv[1];
  failureCommand = argv[2];

#if defined _WIN32 || defined _WIN64
  successCommand = "start " + successCommand;
  failureCommand = "start " + failureCommand;
#elif defined __APPLE__ || defined __linux
  successCommand += " &";
  failureCommand += " &";
#endif

  initialized = true;
}

void Executor::resetExecutor()
{
  commandExecuted = false;
}

bool Executor::executeCommand(Executor::CommandType type)
{
  if (commandExecuted && initialized)
    return false;

  if (type == Executor::CommandType::SUCCESS)
  {
    std::cout << "[Executor] executing command " << successCommand << std::endl;
    system(successCommand.c_str());
    commandExecuted = true;
    return true;
  }
  else if (type == Executor::CommandType::FAILURE)
  {
    std::cout << "[Executor] executing command " << failureCommand << std::endl;
    system(failureCommand.c_str());
    commandExecuted = true;
    return true;
  }

  return false;
}