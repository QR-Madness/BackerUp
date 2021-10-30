#pragma once
#include <iostream>
#include <list>
// \/ Include Profiles Here  \/
// /\ Profiles above /\

//Program Global Information
const  std::string BackerUpVersion = "0.1";
//End of Program Global Information

//CONFIGURATION TOOLS
//Returns all profile properties
//std::string getProfileProps();
//END OF CONFIGURATION TOOLS

//Profile Configuration
class BackerUpProfile {
public:
	//Vars, data
	struct BackupLocation {
		int id = 0;
		int priorty = 9999;
		std::string path = "";
		//Resets values of struct
		void erase();
	};
	std::list<BackupLocation> backupInputList;
	//General
	void printProfileConfiguration();
	//Backup paths
	void addBackupPath(std::string path);
	void editBackupPath(std::string path, std::string pathReplacement);
	void clearPaths();
	//Output
	void setDestination(std::string destination);
	void clearDestination();
	std::string getDestination();
	void printBackupPaths();
private:
	//Vars. data
	//Backup variables
	std::string backupDestination;
	bool isConfigured = false;
	//GENERAL
	//Contains master array of paths to be backed up
	//std::string backedUpPaths[];
	//ENCRYPTION
};