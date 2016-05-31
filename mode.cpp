#include "mode.hpp"

Mode::Mode(const std::string &_name, const int _priority)
  : name(_name),
    priority(_priority)
{
}

void Mode::setName(const std::string &value)
{
  name = value;
}

std::string Mode::getName() const
{
  return name;
}

int Mode::getPriority() const
{
  return priority;
}

void Mode::setPriority(int value)
{
  priority = value;
}
