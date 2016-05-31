#include "prioritymap.hpp"
#include <iostream>

// TODO Add modes and override run(); using static_cast or dynamic_cast add different Mode-types to the map
// TODO Add mode execution class
// TODO Clean properly - also change normal pointers to boost::smart pointers
// TODO Use signals triggered from Mode to map to tell map that a mode execution has finished or timedout in which case it has to be deleted from map (if last mode in a PriorityGroup delete whole group)

int main ()
{
  PriorityMap *priorities = new PriorityMap();
  Mode *m1 = new Mode("m1", 0);
  priorities->insert(m1);

  Mode *m2 = new Mode("m2", 0);
  priorities->insert(m2);

  Mode *m3 = new Mode("m3", 1);
  priorities->insert(m3);

  priorities->print();

  delete priorities;

  return 0;
}
