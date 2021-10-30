//Standard Library Requirments
#include <iostream>
//Includes core functionalities
#include "../include/core.hpp"
/*
TODO LIST:
Profile Files
Disk Manager; Move backups to removable medias
Encryption Implementation

Compilation CMD : cl /std:c++20 src/* 
*/
using namespace std;

void main() {
	//Variables
	std::string response = "";

	//INITIALIZING SERVICES
	//Creating and configuring Profile
	BackerUpProfile ProfileMain;
	//ProfileMain.addBackupPath("./TESTING_DIR/in/in1");
	//ProfileMain.setDestination("./TESTING_DIR/out");
	//Initalizing Logger
	BackerUpLogger Logger("logger/LoggerError.log");
	//Initalizing Shell
	CommandShell Shell;
	//Initalizing Mover
	BackerUpMoverUtil Mover;

	//Initializing user interaface
	cout << Shell.CommandStringStorage.banner;
	cout << getVersion() << endl;
	cout << "type \"help\" for help" << endl;

	//DEBUG SECTION
	//Mover.printDirectory("./test");
	//Mover.writeBackup(ProfileMain);


	//Starting shell
	while (true) {
		response = Shell.promptUserCmd("BU_Main");
		Shell.executeCommand(response, ProfileMain, Mover, Logger);
	}
}