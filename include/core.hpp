#include <iostream>
#include <unordered_map>

//Includes program's configuration
#include "../include/config_global.hpp"
//Log Manager
#include "../include/errorLog.hpp"
//Backup manager and file utilities
#include "../include/mover.hpp"
using namespace std;

//Returns version of backerup main
const std::string Version_Main = "BackerUp v0.90";
std::string getVersion();

//Shell for command execution and core UI
class CommandShell {
public:
	//CONSTRUCTOR
	//Constructor computes map of commands
	CommandShell();

	//Retrives string based user input 
	std::string promptUserCmd(std::string promptText);

	//Retrives multi type user input, process under certain conditions, returns bundle of types assigned based on conditions
	struct PromptResponse {
		int response_int;
		std::string response_str;
		bool response_tf;
	};
	PromptResponse promptUserCmd(std::string promptText, std::string conditions);

	//Executes command | Returns handler code
	//int executeCommand(std::string command);
	// 
	//Executes command | Contains Command Handler
	int executeCommand(std::string command, BackerUpProfile& Profile, BackerUpMoverUtil& Mover, BackerUpLogger& Logger);

	//####COMMAND std::string STORAGE####
	struct CmdStringStorage {
		const char* banner =
			R"V0G0N(
|       \                  |  \                       |  \  |  \         
| ▓▓▓▓▓▓▓\ ______   _______| ▓▓   __  ______   ______ | ▓▓  | ▓▓ ______  
| ▓▓__/ ▓▓|      \ /       \ ▓▓  /  \/      \ /      \| ▓▓  | ▓▓/      \ 
| ▓▓    ▓▓ \▓▓▓▓▓▓\  ▓▓▓▓▓▓▓ ▓▓_/  ▓▓  ▓▓▓▓▓▓\  ▓▓▓▓▓▓\ ▓▓  | ▓▓  ▓▓▓▓▓▓\
| ▓▓▓▓▓▓▓\/      ▓▓ ▓▓     | ▓▓   ▓▓| ▓▓    ▓▓ ▓▓   \▓▓ ▓▓  | ▓▓ ▓▓  | ▓▓
| ▓▓__/ ▓▓  ▓▓▓▓▓▓▓ ▓▓_____| ▓▓▓▓▓▓\| ▓▓▓▓▓▓▓▓ ▓▓     | ▓▓__/ ▓▓ ▓▓__/ ▓▓
| ▓▓    ▓▓\▓▓    ▓▓\▓▓     \ ▓▓  \▓▓\\▓▓     \ ▓▓      \▓▓    ▓▓ ▓▓    ▓▓
 \▓▓▓▓▓▓▓  \▓▓▓▓▓▓▓ \▓▓▓▓▓▓▓\▓▓   \▓▓ \▓▓▓▓▓▓▓\▓▓       \▓▓▓▓▓▓| ▓▓▓▓▓▓▓ 
                                                               | ▓▓      
                                                               | ▓▓      
                                                                \▓▓      
)V0G0N";
		const char* command_unrecognized = "Error: Command Unrecognized";
		const char* help_init =
			R"V0G0N(
###PROGRAM LIST###
exit - ...
help - show commands, help
info - show program, build info
backup - launch main backup utility
profile - profile manager
##############
)V0G0N";

		const char* backup_command_list =
			R"V0G0N(
###Backup Manager Controls###
back
show profile
make backup
####################
)V0G0N";

		const char* profile_command_list =
			R"V0G0N(
##Profile Manager Controls###
back
show
set [OPTION]
	input - path(s) to backup
	output - destination to place backup folder
####################
)V0G0N";
	};
	//####END OF COMMAND std::string STORAGE####
	CmdStringStorage CommandStringStorage;
private:
	//Private variables declaration
	unordered_map<std::string, int> cmd_map;
};

