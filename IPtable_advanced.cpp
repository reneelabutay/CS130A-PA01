//IPtable_advanced.cpp

#include "IPtable_advanced.h"
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <math.h>

IPtable_advanced::IPtable_advanced(int input) {
  this->b = (int)log2(input);
  
  this->size = findNextPrime(input);
  table.resize(size);

  randomInts.resize(ceil(((double)32)/this->b));  
  for(int i = 0; i < (int)randomInts.size(); i++) {
    randomInts[i] = rand() % size;
  }
  
  this->numInserted = 0;
  this->numDeleted = 0;
  this->singleSlots = 0;
  this->emptySlots = size;
  this->maxCollisions.first = -1;
  this->maxCollisions.second = -1;
}

//hashes IP address into slot in table
int IPtable_advanced::hash(std::string IP) {

  std::vector<int> inputs; //will store groups of the bytes separated by '.'  
  
  std::istringstream iss(IP);
  std::string num;

  while(std::getline(iss,num,'.')) {
    if(!num.empty()) {
      inputs.push_back(std::stoi(num));
    }
  }
  
  std::string allBinaryNum;
  //convert each byte to binary, then add to a string
  for(int i = 0; i < (int)inputs.size(); i++) {
    std::bitset<8> bit(inputs[i]);
    allBinaryNum += bit.to_string();
  }

  std::vector<std::string> binarySubs;
  for(int i = 0; i < (int)allBinaryNum.length();) {
    if(i == 0 && (32%this->b)!= 0) {
      binarySubs.push_back(allBinaryNum.substr(i, (32%this->b)));
      i += (32%this->b);
    } else {
      binarySubs.push_back(allBinaryNum.substr(i,b));
      i += b;
    }    
  }

  std::vector<int> values;
  for(int i = 0; i < (int)binarySubs.size(); i++) {
    values.push_back(std::stoi(binarySubs[i], nullptr, 2));
  }
  
  int sum = 0;
  for(int i = 0; i < (int)values.size(); i++) {
    sum += (values[i] * this->randomInts[i]);
  }
  
  return sum % this->size;
}

int IPtable_advanced::findNextPrime(int num) {
  int prime = num;
  while(!isPrime(prime)) {
    prime++;
  }
  return prime;
}

bool IPtable_advanced::isPrime(int num) {
  int it = 2;
  while(it <= (int)sqrt(num)) {
    if(num % it == 0) {
      return false;
    } else {
      it++;
    }
  }
  return true;
}

//Check if it exists in the table already
bool IPtable_advanced::exists(std::string IP) {
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
void IPtable_advanced::insert(std::string IP) {
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
void IPtable_advanced::remove(std::string IP) {
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
std::string IPtable_advanced::lookup(std::string IP) {
  
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
void IPtable_advanced::stat() {

  //Prints a1,a2,a3...

  for(int i = this->randomInts.size() - 1; i >= 0; i--) {
    std::cout << randomInts[i] << " ";
  }
  std::cout<<std::endl;
  //std::cout << this->a << " " << this->b << " " << this->c << " " << this->d << std::endl;
  std::cout << this->numInserted << std::endl;
  std::cout << this->numDeleted << std::endl;
  std::cout << this->emptySlots << std::endl;
  std::cout << this->singleSlots << std::endl;
  std::cout << this->maxCollisions.first << " " << this->maxCollisions.second << std:: endl;
}
