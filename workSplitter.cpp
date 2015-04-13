

#include "pstream.h"
#include <vector>
#include <iostream>
#include <fstream>


int main(int argc, char** argv){

  using namespace redi;
  
  const std::string usage = "./workSplitter <listOfMachines.txt> <list of commands>";

  if(argc != 3){
	std::cout << usage << std::endl;
	return 1;
  }

  std::vector<std::string> machines, commands;

	
  std::string line;
  std::ifstream machineFile(argv[1]);
  while(std::getline(machineFile, line)){
	machines.push_back(line);
  }
  std::ifstream commandFile(argv[2]);
  while(std::getline(commandFile, line)){
	commands.push_back(line);
  }
  std::reverse(commands.begin(), commands.end());
  //so we can just pop off the back task when we're ready to go

  std::vector<ipstream> streams(machines.size());
  while(!commands.empty()){
	for(auto i = 0; i < machines.size(); ++i){
	  std::cout << "checking machine: " << machines[i] << std::endl;
	  if(!streams[i].is_open() || streams[i].rdbuf()->exited()){
		streams[i].close(); //just in case
		std::string toRun = std::string("ssh ") + machines[i] + " '" + commands.back() + "'";
		std::cout << "about to run: " << toRun << std::endl;
		streams[i].open(toRun);
		commands.pop_back();
		if(commands.empty()){break;}
	  }
	}
	sleep(1);
  }
  std::cout << "waiting for children to exit" << std::endl;
  return 0;
}
