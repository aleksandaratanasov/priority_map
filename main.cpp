#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

// TODO Add modes and override run(); using static_cast or dynamic_cast add different Mode-types to the map
// TODO Add mode execution class
// TODO Clean properly (move to shared_ptr or even to boost for the pointers -> a bit of an overkill to take boost just for that :D)

class Mode
{
    std::string name;
    int priority;
  public:
    Mode() {}
    Mode(const std::string &_name, const int _priority)
      : name(_name),
        priority(_priority)
    {
    }

    void setName(const std::string &value)
    {
      name = value;
    }

    std::string getName() const
    {
      return name;
    }

    int getPriority() const
    {
      return priority;
    }

    void setPriority(int value)
    {
      priority = value;
    }

    //virtual void run() = 0;
};

class PriorityMap
{
    typedef std::pair<int, Mode *> ModeEntry;
    typedef std::map<int, Mode *> PriorityGroup;
    typedef PriorityGroup* PriorityGroup_Ptr;
    typedef std::map<int, PriorityGroup_Ptr> Priority;
    typedef Priority* Priority_Ptr;

    Priority_Ptr priorities;
  public:
    PriorityMap() {
      priorities = new Priority();
    }

    ~PriorityMap() {
      // http://stackoverflow.com/a/19970551/1559401
      // for each entry of priorities: priorityGroup.second (get prio group)
      // for each prio group delete modeEntry.second (--->Mode *)
      // delete priorityGroup
      // delete priorities

      delete priorities;
    }

    void print() {
      for(const auto& priorityGroup : *priorities) {
        std::cout << "[" << priorityGroup.first << "]:" << std::endl;
        for(auto& modeEntry : *(priorityGroup.second))
          std::cout << "\t <" << modeEntry.first << " : \"" << modeEntry.second->getName() << "\">" << std::endl;
      }
    }

    bool insert(Mode *mode) {
      if(!mode) return false;

      PriorityGroup_Ptr priorityGroup;
      // Try to find a priority group for the given mode
      auto foundPriorityGroup = priorities->find(mode->getPriority());
      // If the end was reached and no group was found, a new one is created
      if(foundPriorityGroup == priorities->end()) {
        // Create new priority group
        priorityGroup = new PriorityGroup();
        // Insert the new priority group with a key equal to the given mode's priority
        std::pair<int, PriorityGroup_Ptr> priorityGroupEntry(mode->getPriority(), priorityGroup);
        if(!priorities->insert(priorityGroupEntry).second) return false;
      }
      else priorityGroup = foundPriorityGroup->second;

      bool entryInserted = false;
      int key = 0;
      // Generate new key - iterate from 0 to the highest key in the priority group and assign the first available one to the new mode entry
      // Break if entry insertion was successful or the end of the priority group has been reached
      if(priorityGroup->size())
        for(; key <= priorityGroup->rbegin()->first || entryInserted; ++key) {
          // Try inserting new entry with current key
          entryInserted = priorityGroup->insert(ModeEntry(key, mode)).second;
        }

      // If end of priority group has been reached but entry insertion has failed we try one more time by adding a new key
      if(!entryInserted) {
        key = key++;
        return priorityGroup->insert(ModeEntry(key, mode)).second;
      }

    }
};

void insert(PriorityMap *priorityMap, Mode *mode) {
  if(!priorityMap || !mode) return;

  if(priorityMap->insert(mode)) std::cout << "Inserted \"" << mode->getName() << "\" with priority " << mode->getPriority() << " SUCCESSFUL" << std::endl;
  else std::cout << "Inserted \"" << mode->getName() << "\" with priority " << mode->getPriority() << " FAILED" << std::endl;

}

int main ()
{
  PriorityMap *priorities = new PriorityMap();
  Mode *m1 = new Mode("m1", 0);
  insert(priorities, m1);

  Mode *m2 = new Mode("m2", 0);
  insert(priorities, m2);

  Mode *m3 = new Mode("m3", 1);
  insert(priorities, m3);

  priorities->print();

  delete priorities;

  return 0;
}
