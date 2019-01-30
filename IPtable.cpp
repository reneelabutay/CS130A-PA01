//IPtable.cpp

#include "IPtable.h"
#include <iostream>
#include <sstream>
#include <string>

//Constructor
IPtable::IPtable(int size) {
  this->size = size+1;
  table.resize(size);
  
  this->emptySlots = this->size;
  this->numInserted = 0;
  this->numDeleted = 0;
  this->singleSlots = 0;

  this->a = rand() % 257;
  this->b = rand() % 257;
  this->c = rand() % 257;
  this->d = rand() % 257;

  this->maxCollisions.first = -1;
  this->maxCollisions.second = -1;
}

//Hash Function
int IPtable::hash(std::string IP) {

  //parse the string into ints
  std::vector<int> bytes;

  std::istringstream iss(IP);
  std::string byte;

  while(std::getline(iss,byte, '.')) {
    if(!byte.empty())
      //convert the string to int first
      bytes.push_back(std::stoi(byte));
  }

  int sum = 0;
  sum += this->d * bytes[0];
  sum += this->c * bytes[1];
  sum += this->b * bytes[2];
  sum += this->a * bytes[3];
  
  return sum % 257;
}

//Check if it exists in the table already
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

//Adds the IP address into the table
void IPtable::insert(std::string IP) {
  if(exists(IP)) {
    //error!
    std::cout << "Error : could not insert " << IP << " because it already exists." << std::endl;
    return;
  }
  int index = hash(IP);
  if(table[index].empty()) {
    table[index].push_back(IP);
    singleSlots ++;
    emptySlots--;
    if(this->maxCollisions.first < 1) {
      this->maxCollisions.first = table[index].size();
      this->maxCollisions.second = index;
    } else if (this->maxCollisions.first == 1 && this->maxCollisions.second < index) {
      this->maxCollisions.second = index;
    }
    
  } else {
    //separate chaining, insert at front
    if(table[index].size() == 1) {
      this->singleSlots --;
    }
    table[index].push_front(IP);

    if((int)table[index].size() > this->maxCollisions.first) {
      this->maxCollisions.first = table[index].size();
      this->maxCollisions.second = index;
    } else if ((int)table[index].size() == this->maxCollisions.first) {
      if(index > this->maxCollisions.second) {
	this->maxCollisions.first = table[index].size();
	this->maxCollisions.second = index;
      }
    }
  }

  this->numInserted ++;
  return;
}

//Deletes IP address into the table
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
	this->singleSlots--;
      } else if(table[index].size() == 1) {
	this->singleSlots++;
      }
      
      return;
    }
  }

  std::cout << "Error : could not delete " << IP << " because it does not exist." << std::endl;
  return;
}

//States if the value is found in the array
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

//Prints out stats of the table
void IPtable::stat() {
  std::cout << this->a << " " << this->b << " " << this->c << " " << this->d << std::endl;
  std::cout << this->numInserted << std::endl;
  std::cout << this->numDeleted << std::endl;
  std::cout << this->emptySlots << std::endl;
  std::cout << this->singleSlots << std::endl;
  std::cout << this->maxCollisions.first << " " << this->maxCollisions.second << std:: endl;
}
