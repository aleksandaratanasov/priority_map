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

    bool _insert(Mode *mode);
  public:
    PriorityMap();
    ~PriorityMap();

    void print();
    void insert(Mode *mode);
};

#endif // PRIORITYMAP_HPP
