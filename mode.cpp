#include "mode.hpp"
#include <iostream>
#include <unistd.h>

Mode::Mode()
{
}

Mode::Mode(const std::string &_name, const int _priority)
    : name(_name),
    priority(_priority),
    id(-1)
{
}

Mode::~Mode()
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

int Mode::getId() const
{
    return id;
}

void Mode::setId(int value)
{
    id = value;
}

ModeSleep::ModeSleep()
  : Mode()
{
  ms = 0;
}

ModeSleep::ModeSleep(const std::string &name, const int priority, const unsigned int _loops)
  : Mode(name, priority),
    ms(_loops)
{
}

ModeSleep::~ModeSleep()
{
}

unsigned int ModeSleep::getMilliseconds() const
{
  return ms;
}

void ModeSleep::setMicroseconds(unsigned int value)
{
  ms = value;
}

void ModeSleep::run()
{
  usleep(ms*1000);
}

ModeFactorial::ModeFactorial()
  : Mode(),
    value(0),
    result(0)
{
}

ModeFactorial::ModeFactorial(const std::string &name, const int priority, const unsigned  int _value)
  : Mode(name, priority),
    value(_value),
    result(0)
{
}

ModeFactorial::~ModeFactorial()
{
}

unsigned int ModeFactorial::getResult() const
{
  return result;
}

void ModeFactorial::setValue(unsigned int value)
{
  value = value;
}

void ModeFactorial::run()
{
  result = 1;
  for(unsigned int i = 1; i <= value; ++i)
      result *= i;
}
