#pragma once
#include <fstream>
using namespace std;

class BackerUpLogger {
public:
	/*
	######FORMAT ENTITY LIST######
	*/
	struct FormatEntities {
		std::string content;
		//Format type layouts
		const std::string format_General = "t m ts";

		//**CURRENT**
		//Format entity list
		const std::string fTitle = "t";
		const std::string fMessage = "msg";
		const std::string fTimestamp = "ts";
		//**FUTURE**
		const std::string fErrCode = "ec";
	};
	//######################

	/*
	#####LOG DATA WRITE PACKET#######
	*/
	struct LogData {
		bool LOG_WRITE_SWITCH = false;
		//Format contains order of format entities
		std::string entityFormat;
		//Contains fully formatted log output std::string
		std::string LogMessageFormatted;
		//Defining message
		int codeNo;
		std::string title;
		std::string message;
		std::string timestamp;
	};
	//###########################

	//Global Class Variables
	FormatEntities EntityList;

	//####FORMATTING FUNCTIONS####
	//Returns current timestamp
	std::string getTimestamp();
	//Takes a format code and returns the definition
	std::string defineFormatSymbol(std::string symbol, LogData LogInfo);
	//########################

	//CONSTRUCTOR
	BackerUpLogger(std::string logPath);

	//##################General Functions############################
	//Formats logging parameters to log struct
	LogData genLogData(std::string title, std::string message, bool timestamp, std::string outputFormat);
	//Writes to file using generated log data
	bool writeToFile(LogData LogParameters);
	//#########################################################

private:
	//Constructor
	BackerUpLogger();

	//Backend Variables
	fstream logFile;
	bool fileOpened = false;
};