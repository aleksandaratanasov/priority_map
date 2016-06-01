#include "prioritymap.hpp"
#include <iostream>
#include <exception>

// TODO Add mode execution class
// TODO Clean properly - also change normal pointers to boost::smart pointers
// TODO Use signals triggered from Mode to map to tell map that a mode execution has finished or timedout in which case it has to be deleted from map (if last mode in a PriorityGroup delete whole group)

int main ()
{
  PriorityMap *priorities = new PriorityMap();
  ModeSleep *m1 = new ModeSleep("Sleep10", 0, 10);
  int m1Id = 0;
  priorities->insert(m1, m1Id);

  ModeSleep *m2 = new ModeSleep("Sleep5", 0, 5);
  int m2Id = 0;
  priorities->insert(m2, m2Id);

  ModeFactorial *m3 = new ModeFactorial("Factorial20", 1, 20);
  int m3Id = 0;
  priorities->insert(m3, m3Id);

  priorities->print();

//  ModeSleep *foundM2 =  priorities->template find<ModeSleep>("Sleep5");
//  if(foundM2)
//    std::cout << "Found mode \"" << foundM2->getName() << "\" has time interval set to " << foundM2->getMilliseconds() << "ms" << std::endl;

  //ModeSleep *foundM1 = priorities->find<ModeSleep>("Factorial20");

  delete priorities;

  return 0;
}
