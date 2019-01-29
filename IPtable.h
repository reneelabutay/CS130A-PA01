//IPtable.h

#ifndef IPTABLE_H
#define IPTABLE_H

#include <string>
#include <list>
#include <vector>
#include <iostream>

class IPtable {
 public:
  
  IPtable(int size);

  void insert(std::string IP);
  //adds IP into the hash table
  
  void remove(std::string IP);
  //remove IP from the hash table if it is present
  
  std::string lookup(std::string IP);
  //checks to see if the IP address is currently in the hash table

  bool exists(std::string IP);
  //helper function for lookup
    
  void stat();
  //prints out the statistics of the IPtable
  
 private:
  int size;

  int a;
  int b;
  int c;
  int d;

  int numInserted;
  int numDeleted;

  int emptySlots;

  int singleSlots;
  
  std::pair <int, int> maxCollisions;
  
  std::vector<std::list<std::string>> table;
  //hash table will be a vector of list
  
  int hash(std::string IP);
  //hash function that will output the index for the IP address
  //in the table
};

#endif
