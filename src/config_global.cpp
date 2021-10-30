#include "../include/config_global.hpp"
#include <filesystem>
#include <sstream>
using namespace std;
namespace fs = filesystem;

void BackerUpProfile::BackupLocation::erase()
{
	id = BackupLocation::id;
	priorty = BackupLocation::priorty;
	path.clear();
}
void BackerUpProfile::printProfileConfiguration()
{
	cout << "**Input(s) / Backup Path(s)**" << endl;
	printBackupPaths();
	cout << endl;
	cout << "No of Paths to backup: " << backupInputList.size() << endl;
	cout << "**Output**" << endl << backupDestination << endl;
}
void BackerUpProfile::printBackupPaths()
{
	list<BackupLocation>::iterator itr;
	for (itr = backupInputList.begin(); itr != backupInputList.end(); itr++) {
		cout << "ID_" << itr->id << " :: " << itr->path << " | Priority " << itr->priorty << endl;
	}
	return;
}
void BackerUpProfile::addBackupPath(std::string path)
{
	//backupInputList.push_back(path);
	BackupLocation in;
	in.path = path;
	//in.id = currentID;
	//currentID++;
	backupInputList.push_back(in);
	return;
}
void BackerUpProfile::editBackupPath(std::string path, std::string pathReplacement)
{
	list<BackupLocation>::iterator itr;
	//backupInputList.remove_if(path);
	//itr = find_if(backupInputList.begin(), backupInputList.end(), path);
	itr = backupInputList.begin();
	for (bool loopExit = false; loopExit != true;) {
		if (itr->path == path) {
			itr->path = pathReplacement;
			loopExit = true;
		}
		else if (itr == backupInputList.end()) { loopExit == true; }
		else { itr++; }
	}
	return;
}
void BackerUpProfile::clearPaths()
{
	list<BackupLocation>::iterator itr;
	itr = backupInputList.begin();
	//Removing all elements before last
	for (itr = backupInputList.begin(); itr != backupInputList.end(); itr++) {itr = backupInputList.erase(itr);}
	//Removing last element
	backupInputList.erase(backupInputList.begin());
	return;
}
void BackerUpProfile::setDestination(std::string destination)
{
	backupDestination = destination;
}
void BackerUpProfile::clearDestination()
{
	setDestination("");
}
std::string BackerUpProfile::getDestination()
{
	return backupDestination;
}