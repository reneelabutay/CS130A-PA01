//IPtable.h

#ifdef IPTABLE_H
#define IPTABLE_H

#include <string>
#include <list>
#include <vector>


class IPtable {

 public:
  
  IPtable(int size);

  void insert(std::string IP);
  //adds IP into the hash table
  
  void delete(std::string IP);
  //remove IP from the hash table if it is present
  
  string lookup(std::string IP);
  //checks to see if the IP address is currently in the hash table
 private:
  int size;

  std::vector<std::list<std::string>> table;
  //hash table will be a vector of list
  
  int hash(std::string IP);
  //hash function that will output the index for the IP address
  //in the table
}

#endif
