#ifndef PRIORITYMAP_HPP
#define PRIORITYMAP_HPP

#include "mode.hpp"
#include <map>
#include <iostream>

class PriorityMap
{
    typedef std::pair<int, Mode *> ModeEntry;
    typedef std::map<int, Mode *> PriorityGroup;
    typedef PriorityGroup* PriorityGroup_Ptr;
    typedef std::map<int, PriorityGroup_Ptr> Priority;
    typedef Priority* Priority_Ptr;

    Priority_Ptr priorities;

    bool _insert(Mode *mode, int &_id);
    Mode *_find(const std::string &name);
  public:
    PriorityMap();
    ~PriorityMap();

    void print();
    void insert(Mode *mode, int &_id);
    // TODO find should return a vector of pointers since names are not unique which means that we can have multiple modes with the same name independent from
    // the priority group they belong to! Right now find() returns the first match!
    template<class T> T *find(const std::string &name)
    {
      Mode *foundMode = _find(name);
      if(foundMode) {
        T *foundModeCast = dynamic_cast<T *>(foundMode);
        if(foundModeCast) {
          std::cout << "Found mode \"" << foundModeCast->getName() << "\"" << std::endl;
          return foundModeCast;
        }
        else {
          std::cout << "Found mode \"" << foundMode->getName() << "\" however specified type is invalid! Returning NULL" << std::endl;
          return nullptr;
        }
      }
    }
};

#endif // PRIORITYMAP_HPP
