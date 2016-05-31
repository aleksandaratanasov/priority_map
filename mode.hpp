#ifndef MODE_HPP
#define MODE_HPP

#include <string>

class Mode
{
    std::string name;
    int priority;
  public:
    Mode() {}
    Mode(const std::string &_name, const int _priority);

    void setName(const std::string &value);
    std::string getName() const;

    int getPriority() const;
    void setPriority(int value);

    //virtual void run() = 0;
};

#endif // MODE_HPP
