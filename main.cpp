//main.cpp

#include "IPtable.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


int main () {
  std::string line;

  std::getline(std::cin,line);
  //std::cout<<"line: "<<line<<std::endl;;
  int size = std::stoi(line);
  IPtable table(size);
  
  while(std::getline(std::cin,line)) {
    //call stat
    if(line.length() == 4) {
      table.stat();
    } else {
      std::string command = line.substr(0,6);
      std::string IPaddress = line.substr(7);

      if(command == "insert") {
	table.insert(IPaddress);
      } else if (command == "delete") {
	table.remove(IPaddress);
      } else if (command == "lookup") {
	std::cout << table.lookup(IPaddress) <<std::endl;
      }
    }
    }
}
