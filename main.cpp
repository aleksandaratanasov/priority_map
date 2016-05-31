#include "prioritymap.hpp"
#include <iostream>

// TODO Add mode execution class
// TODO Clean properly - also change normal pointers to boost::smart pointers
// TODO Use signals triggered from Mode to map to tell map that a mode execution has finished or timedout in which case it has to be deleted from map (if last mode in a PriorityGroup delete whole group)

int main ()
{
  PriorityMap *priorities = new PriorityMap();
  ModeSleep *m1 = new ModeSleep("Sleep10", 0, 10);
  priorities->insert(m1);

  ModeSleep *m2 = new ModeSleep("Sleep5", 0, 5);
  priorities->insert(m2);

  ModeFactorial *m3 = new ModeFactorial("Factorial20", 1, 20);
  priorities->insert(m3);

  priorities->print();

  delete priorities;

  return 0;
}
