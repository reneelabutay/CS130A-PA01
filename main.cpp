//main.cpp

#include "IPtable.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


int main (int argv, char ** argc) {
  if(argv < 2) {
    std::cout << "Please provide a file name" << std::endl;
    return 1;
  }

  std::ifstream inputFile(argc[1]);
  
  if(inputFile.fail()) {
    std::cout<<"Invalid file."<<std::endl;
    return 1;
  }

  std::string line;

  //this will be the size of the table, convert the string to int
  getline(inputFile,line);
  
  int size = std::stoi(line);

  //initializes IPtable object 
  IPtable table(size);
  
  while(getline(inputFile,line)) {

    //call stat
    if(line.length() == 4) {
      table.stat();
    } else {
      
      std::string command = line.substr(0,6);
      std::string IPaddress = line.substr(7);

      //std::cout<<command<<"        "<<IPaddress<<std::endl;
      if(command == "insert") {
	table.insert(IPaddress);
      } else if (command == "delete") {
	table.remove(IPaddress);
      } else if (command == "lookup") {
	std::cout << table.lookup(IPaddress) << std::endl;
      }
    }
  }

  return 0;
}
