//IPtable.cpp

#include "IPtable.h"
#include <iostream>
#include <sstream>
#include <string>

IPtable::IPtable(int size) {
  this->size = size;
  table.resize(size);
  
  this->emptySlots = size;
  this->numInserted = 0;
  this->numDeleted = 0;
  this->singleSlots = 0;
}

int IPtable::hash(std::string IP) {

  //parse the string into ints
  std::vector<int> values;

  std::istringstream iss(IP);
  std::string byte;

  while(std::getline(iss,byte, '.')) {
    if(!byte.empty())
      //convert the string to int first
      values.push_back(std::stoi(byte));
  }
  //values contain the bytes

  int sum = 0;
  sum += this->d * values[0];
  sum += this->c * values[1];
  sum += this->b * values[2];
  sum += this->a * values[3];
  
  return sum % 257;
}

bool IPtable::exists(std::string IP) {
  int index = hash(IP);
  std::list<std::string>::iterator it;
  for(it = table[index].begin(); it != table[index].end(); it++){
    if(IP.compare(*it) == 0){
      return true;
    }
  }
  return false;
}

void IPtable::insert(std::string IP) {

  if(exists(IP)) {
    //error!
    std::cout << "Error : could not insert " << IP << " because it already exists." << std::endl;
    return;
  }

  int index = hash(IP);
  if(table[index].empty()) {
    table[index].push_back(IP);
    emptySlots--;
  } else {
    //separate chaining, insert at front
    table[index].push_front(IP);
  }
  this->numInserted ++;
  return;
}

void IPtable::remove(std::string IP) {
  int index = hash(IP);
  std::list<std::string>::iterator it;
  for(it = table[index].begin(); it!=table[index].end(); it++) {
    if(IP.compare(*it) == 0) {
      //delete the value
      table[index].erase(it);
      numDeleted ++;

      if(table[index].empty()) {
	this->emptySlots++;
      }
      
      return;
    }
  }

  std::cout << "Error : could not delete " << IP << " because it does not exist." << std::endl;
  return;
}

std::string IPtable::lookup(std::string IP) {
  
  std::string output = IP;

  bool exist = exists(IP);
  
  if (exist) {
    output += ": found.";
  } else {
    output += ": not found.";
  }

  return output;
}

void IPtable::stat() {
  std::cout << this->a << " " << this->b << " " << this->c << " " << this->d << std::endl;
  std::cout << this->numInserted << std::endl;
  std::cout << this->numDeleted << std::endl;
  std::cout << this->emptySlots << std::endl;
}
