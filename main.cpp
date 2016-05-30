#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

#include <iostream>
#include <map>
#include <vector>

typedef int Priority;
typedef int Mode_ID;

typedef struct {
  Priority priority;
  std::string name;
} Mode;

// Outer map - PriorityMap - contains entries where a priority is the keys
// Inner map - PriorityGroup - contains entries where an automatically generated key is used to an entry's value - a Mode - with all modes having the same priority
typedef std::map<Priority, std::map<Mode_ID, Mode> > PriorityMap;
typedef std::pair<Priority, PriorityGroup> PriorityMapInsertion;
typedef std::map<Mode_ID, Mode> PriorityGroup;

bool insertMode(PriorityMap& priorityMap, Mode *mode) {
  
  auto foundPrioEntry = priorityMap.find(mode->priority);
  bool createdPriorityGroupOkay = false;
  
  // If no priority equal to mode->priority is available create a new PriorityGroup
  if(foundPrioEntry == priorityMap.end())
    createdPriorityGroupOkay = priorityMap.insert(
      std::pair<Priority, PriorityGroup>(
	mode->priority,
	PriorityGroup()
      )
    );
  
  //if(!createdPriorityGroupOkay) return false;
  
  // If PriorityGroup was succcessfully created attempt to add mode to it
  PriorityGroup modes = foundPrioEntry->second(); // Retrieve map of modes with same priority
  Mode_ID modeKey = 0;
  bool insertOkay = false;
  int key = 0;
  for(; key < modes.rbegin()->first(); key++)  { // modes.rbegin() returns the entry at the end of the ModeMap which contains the biggest key
    // Start from the first key inside the ModeGroup map and continue until the end is reached (and insertion has failed) or an available key was found
    insertOkay = modes.insert(std::pair<modeKey, mode>); // Attempt to insert with current key
  }
  
  // If insertion has failed (due to lack of available keys)
  if(!insertOkay) {
    // Add a new priority (=key)
    modeKey = key++;
    // And attempt to insert given mode into ModeGroup map
    insertOkay = modes.insert(std::pair<modeKey, mode>);
  }
  
  return insertOkay;
}

int main ()
{
  std::map<char,int> mymap;

  // first insert function version (single parameter):
  std::cout << "Inserting ['a', 1], ['a', 2] and ['b', 2] one after the other" << std::endl;
  mymap.insert( std::pair<char,int>('a',1) );
  mymap.insert( std::pair<char,int>('a',1) );
  mymap.insert( std::pair<char,int>('b',2) );
  std::cout << "Insering bulk items from ['c',3] to ['z',26]" << std::endl;
  std::vector<std::pair<char,int> > bulk_items;
  std::cout << "Filling vector with items: ";
  for(int i = 0; i < 24; ++i) {
    bulk_items.push_back(std::make_pair(char(i+99),i+3));
    std::cout << "[" << char(i+99) << "," << i+3 << "] ";
  }
  std::cout << "\nInserting vector into map" << std::endl;
  mymap.insert(bulk_items.begin(), bulk_items.end());

  std::pair<std::map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( std::pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  std::map<char,int>::iterator it = mymap.begin();
  mymap.insert(it, std::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert(it, std::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  std::map<char,int> anothermap;
  anothermap.insert(mymap.find('k'),mymap.find('t'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  
  
  // Priority 	- mode priority; entries with same priority can be accessed by their priority and the automatically generated mode_id
  // Mode_ID 	- generated and assigned to every mode which is added; used to differentiate between modes with same priority
  // Mode 	- contains a mode entry
  PriorityMap priorities;
  Mode m1 = {0, "m1"};
  priorities.insert(priorities, &m1);

  return 0;
}
