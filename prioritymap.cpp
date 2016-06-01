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

// TODO Add support for unique keys for modes across ALL priority groups. Right now keys are unique only withing the boundries of their priority group
bool PriorityMap::_insert(Mode *mode, int &_id) {
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
    entryInserted = priorityGroup->insert(ModeEntry(key, mode)).second;
  }

  if(entryInserted) mode->setId(key);
  _id = mode->getId();

  return entryInserted;
}

void PriorityMap::insert(Mode *mode, int &_id) {
  if(_insert(mode, _id)) std::cout << "Inserted \"" << mode->getName() << "\" of priority " << mode->getPriority() << " SUCCESSFUL. Mode ID set to " << _id << std::endl;
  else std::cout << "Inserted \"" << mode->getName() << "\" of priority " << mode->getPriority() << " FAILED" << std::endl;

}

// TODO Add support for finding a mode based on its ID
Mode *PriorityMap::_find(const std::string &name)
{
  for(const auto& priorityGroup : *priorities)
    for(auto& modeEntry : *(priorityGroup.second))
      if(!name.compare((modeEntry.second->getName())))
        return modeEntry.second;

  return nullptr;
}

// TODO find should return a vector of pointers since names are not unique which means that we can have multiple modes with the same name independent from
// the priority group they belong to! Right now find() returns the first match!
template<class T>
T *PriorityMap::find(const std::string &name)
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
