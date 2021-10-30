#include <iostream>
#include "../include/config_global.hpp"
#pragma once
class BackerUpMoverUtil {
private:
	int makeBackup(std::string path, std::string destination);
	enum class copy_options;
public:
	//Prints out current directory
	void printDirectory(std::string path);
	//Writes backup using @param profile
	int writeBackup(BackerUpProfile profile);
};