#include <iostream>
#include <sstream>
#include "../include/core.hpp"
#include "../include/config_global.hpp";
#include "../include/errorLog.hpp"
using namespace std;

//Returns version of backerup main
std::string getVersion() {
	return Version_Main;
}
//Shell for command execution and core UI
CommandShell::CommandShell()
{
	/*#############################
	#######COMMAND HANDLER IDS#######
	##############################*/
	cmd_map["help"] = 1;
	cmd_map["info"] = 2;
	cmd_map["exit"] = 3;
	cmd_map["backup"] = 4;
	cmd_map["profile"] = 5;
	/*##############################
	#####END OF COMMAND HANDLER IDS#####
	###############################*/
}
//Retrives user input 
std::string CommandShell::promptUserCmd(std::string promptText)
{
	std::string input = "";
	char input_char[250];
	std::string output = "";
	cout << promptText << " /> ";
	cin.getline(input_char, 250);
	input = input_char;
	output = input;
	return output;
}
//Retrives multi type user input, process under certain conditions
CommandShell::PromptResponse CommandShell::promptUserCmd(std::string promptText, std::string conditions)
{
	std::string strResponse = promptUserCmd(promptText);
	int intResponse = 0;
	bool boolResponse = false;
	stringstream responseStream(strResponse);
	PromptResponse output;
	//Unchanged text
	if (conditions == "text") {
		output.response_str = strResponse;
	}
	//Convert to lower case
	else if (conditions == "text_low") {
		for (int i = 0; i < strResponse.length(); i++) { strResponse[i] = tolower(strResponse[i]); }
	}
	//Grabs first integer
	else if (conditions == "int_basic") {
		responseStream.clear();
		responseStream >> intResponse;
	}
	//Get a positive or negative repsonse
	else if (conditions == "bool") {
		//Convert to lower case
		for (int i = 0; i < strResponse.length(); i++) { strResponse[i] = tolower(strResponse[i]); }
		string responsesY[] = { "yes","ye", "y", "true", "1" , "t" };
		string responsesN[] = { "no", "n", "false", "0", "f" };
		//searching for yes
		for (int i = 0, ctdLen = 0, len = sizeof(responsesY); ctdLen < len; i++, ctdLen += sizeof(responsesY[i])) {
			if (strResponse == responsesY[i]) { boolResponse = true; }
		}
		//searching for no
		for (int i = 0, ctdLen = 0, len = sizeof(responsesN); ctdLen < len; i++, ctdLen += sizeof(responsesN[i])) {
			if (strResponse == responsesN[i]) { boolResponse = false; }
		}
	}
	//Defining struct
	output.response_str = strResponse;
	output.response_int = intResponse;
	output.response_tf = boolResponse;
	return output;
}
//Executes command | Contains Command Handler
int CommandShell::executeCommand(std::string command, BackerUpProfile& Profile, BackerUpMoverUtil& Mover, BackerUpLogger& Logger) {
	//Get command Process Number
	int processNo = 0;
	string response_Str = "";
	string temp_Str = "";
	PromptResponse responseData;
	try {
		processNo = cmd_map.at(command);
	}
	catch (std::out_of_range& err) {
		cout << CommandStringStorage.command_unrecognized << endl;
		return -1;
	}
	/*
	#############################
	#######COMMAND HANDLER#########
	#############################
	*/
	switch (processNo) {
	default:
		break;

	case 0:
		//###############COMMAND###################
		// //--
		//#########################################
		break;

	case 1:
		//###############HELP###################
		cout << CommandStringStorage.help_init;
		//#########################################
		break;

	case 2:
		//###############INFO###################
		cout << getVersion() << endl;
		//#########################################
		break;

	case 3:
		//###############EXIT###################
		exit(EXIT_SUCCESS);
		//#########################################
		break;

	case 4:
		//###############BACKUP###################
		response_Str.clear();
		//Keeping user in backup man prompt
		for (bool exitPrompt = false; exitPrompt != true;) {
			responseData = promptUserCmd("Backup_Man", "text_low");
			response_Str = responseData.response_str;
			if (response_Str == "back") { exitPrompt = true; }
			else if (response_Str == "help") { cout << CommandStringStorage.backup_command_list; }
			else if (response_Str == "show profile") { Profile.printProfileConfiguration(); }
			else if (response_Str == "make backup") { Mover.writeBackup(Profile); }
			else { cout << CommandStringStorage.command_unrecognized << endl; }
		}
		//#########################################
		break;
	case 5:
		//###############PROFILE###################
		response_Str.clear();
		//Keeping user in Profiler prompt
		for (bool exitPrompt = false; exitPrompt != true;) {
			responseData = promptUserCmd("Profile_Man", "text_low");
			response_Str = responseData.response_str;
			if (response_Str == "back") { exitPrompt = true; }
			else if (response_Str == "help") { cout << CommandStringStorage.profile_command_list; }
			else if (response_Str == "show") { Profile.printProfileConfiguration(); }
			else if (response_Str == "set input") {
				cout << "Modifying Input Value(s)" << endl;
				cout << "Type Operation No" << endl << "1 - Add Path(s) | 2 - Edit Path | 3 - Clear Paths" << endl;
				responseData = promptUserCmd("Op No", "int_basic");
				switch (responseData.response_int) {
				default:
					cout << "Unrecongnized" << endl;
					break;
				case 1: // add path
					responseData = promptUserCmd("Full or Rel to binary Path", "text");
					Profile.addBackupPath(responseData.response_str);
					break;
				case 2: //edit path
					responseData = promptUserCmd("Existing Path or ID_XXXX", "text");
					response_Str = responseData.response_str;
					responseData = promptUserCmd("Replacement Path", "text");
					Profile.editBackupPath(response_Str, responseData.response_str);
					break;
				case 3: //clear paths
					responseData = promptUserCmd("Are you sure you want to clear all paths?", "bool");
					if (responseData.response_tf == true) { Profile.clearPaths(); }
					else { break; }
					break;
				}
			}
			else if (response_Str == "set output") {
				cout << "Modifying Output Value(s)" << endl;
				cout << "Type Operation No" << endl << "1 - Add Path(s) | 2 - Reset Output(s)" << endl;
				responseData = promptUserCmd("Op No", "int_basic");
				switch (responseData.response_int) {
				default:
					cout << "Unrecongnized" << endl;
					break;
				case 1: // add path
					responseData = promptUserCmd("Full or Rel to binary Path", "text");
					Profile.setDestination(responseData.response_str);
					break;
				case 2: // clear path
					Profile.clearDestination();
					break;
				}
			}
			else { cout << CommandStringStorage.command_unrecognized << endl; }
		}
		//#########################################
		break;
	}
	/*
	#######END OF COMMAND HANDLER#########
	##################################
	*/
	return 0;
}
/*
##############################################################
###########################FUNCTIONS###########################
##############################################################
*/