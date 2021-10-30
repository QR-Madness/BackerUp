#include <vector>
#include <iostream>
#include <sstream>
#include <ctime> 
//-----LOCAL INCLUDE-----
#include "../include/errorLog.hpp";
//-----------------
using namespace std;

//************BACKEND CORE FUNCTIONS**********
//Returns timestamp format
std::string BackerUpLogger::getTimestamp() {
	char timestamp[30];
	time_t clock;
	struct tm* timeInfo = new tm;

	time(&clock);
	localtime_s(timeInfo, &clock);
	strftime(timestamp, 30, "%c", timeInfo);
	return timestamp;
}
//Defines a format symbol for processed log message
std::string BackerUpLogger::defineFormatSymbol(std::string symbol, LogData LogInfo) {
	//FORMATTING CONTENT
	if (symbol == EntityList.fTitle) { return LogInfo.title; }
	else if (symbol == EntityList.fMessage) { return LogInfo.message; }
	else if (symbol == EntityList.fTimestamp) { return getTimestamp(); }
	else { return ""; }
}
//************END OF BACKEND CORE FUNCTIONS********

/*
############CONSTRUCTORS###############
*/
BackerUpLogger::BackerUpLogger(std::string logPath) {
	logFile.open(logPath, ios::ios_base::app);
	logFile << "*****LOG INIT @ " << getTimestamp() << "******" << endl;
}

//*************MAIN FUNCTIONS********************
BackerUpLogger::LogData BackerUpLogger::genLogData(std::string title, std::string message, bool timestamp, std::string outputFormat) {
	LogData output;
	FormatEntities* Formatter = new FormatEntities;
	std::string temp_string;
	vector<std::string> msgVctr;
	std::string msg_frmtd;

	//Generating std::string stream from message contents
	stringstream stream_msg(outputFormat);

	//Defining LogData
	output.title = title;
	output.message = message;
	output.timestamp = getTimestamp();

	//Moving output format to vector
	while (stream_msg >> temp_string) {
		msgVctr.push_back(temp_string);
	}

	//Creating formatted message 
	for (int i = 0; i < msgVctr.size(); i++) {
		//Getting symbol data
		temp_string = msgVctr[i];
		temp_string = defineFormatSymbol(temp_string, output);
		//Appending data to message
		msg_frmtd += ":::" + temp_string;
	}
	//Defining LogData Formatted Message
	output.LogMessageFormatted = msg_frmtd;

	//Setting write switch
	output.LOG_WRITE_SWITCH = true;

	//CLEANUP 
	delete(Formatter);
	return output;
}

bool BackerUpLogger::writeToFile(LogData LogParameters) {
	if (LogParameters.LOG_WRITE_SWITCH) {
		logFile << LogParameters.LogMessageFormatted << endl;
	}
	else { return false; }
}

//*************END OF FUNCTIONS********************
