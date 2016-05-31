#include "prioritymap.hpp"

#include <algorithm>
#include <memory>

PriorityMap::PriorityMap() {
  priorities = new Priority();
}

PriorityMap::~PriorityMap() {
  std::for_each(priorities->begin(), priorities->end(), [](auto priorityGroup) -> void {
    std::for_each(priorityGroup.second->begin(), priorityGroup.second->end(), [&priorityGroup](auto modeEntry) -> void { // [&priorityGroup] - used to capture priorityGroup (here by reference) from outer lambda so that it's visible in the inner lambda
      std::string name = modeEntry.second->getName();
      delete modeEntry.second;
      std::cout << "Deleted mode \"" << name << "\" in priority group \"" << priorityGroup.first << "\"" << std::endl;
    });

    delete priorityGroup.second;
    std::cout << "Deleted priority group \"" << priorityGroup.first << "\"" << std::endl;
  });

  delete priorities;
}

void PriorityMap::print() {
  std::cout << "--------------------------------------------" << std::endl;
  for(const auto& priorityGroup : *priorities) {
    std::cout << "priority_group \"" << priorityGroup.first << "\"" << std::endl;
    for(auto& modeEntry : *(priorityGroup.second))
      std::cout << "\t <mode_id \"" << modeEntry.first << "\" : mode_name \"" << modeEntry.second->getName() << "\">" << std::endl;
  }
  std::cout << "--------------------------------------------" << std::endl;
}

bool PriorityMap::_insert(Mode *mode) {
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

  return entryInserted;
}

void PriorityMap::insert(Mode *mode) {
  if(_insert(mode)) std::cout << "Inserted \"" << mode->getName() << "\" with priority " << mode->getPriority() << " SUCCESSFUL" << std::endl;
  else std::cout << "Inserted \"" << mode->getName() << "\" with priority " << mode->getPriority() << " FAILED" << std::endl;

}
