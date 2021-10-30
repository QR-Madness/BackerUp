#include "../include/mover.hpp"
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

enum class  BackerUpMoverUtil::copy_options {

	//none = /* unspecified */,
	//skip_existing = /* unspecified */,
	//overwrite_existing = /* unspecified */,
	//update_existing = /* unspecified */,
	//recursive = /* unspecified */,
	//copy_symlinks = /* unspecified */,
	//skip_symlinks = /* unspecified */,
	//directories_only = /* unspecified */,
	//create_symlinks = /* unspecified */,
	//create_hard_links = /* unspecified */
};

int BackerUpMoverUtil::makeBackup(std::string path, std::string destination)
{
	cout << "Making copy of " << path << " to " << destination << endl;
	//Checking path
	if (fs::is_directory(path)) {
		try {
			//Creating folders
			fs::copy(path, destination, fs::copy_options::overwrite_existing | fs::copy_options::directories_only);
			//Creating files
			fs::copy(path, destination, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
			cout << "Folder Moved" << endl;
		}
		catch (fs::filesystem_error& err) {
			cout << "Error writing folder" << endl;
		}
	}
	else if (fs::is_regular_file(path)) {
		try {
			fs::copy(path, destination, fs::copy_options::overwrite_existing);
			cout << "Reg File Moved" << endl;
		}
		catch (fs::filesystem_error& err) {
			cout << "Error writing file" << endl;
		}
	}
	cout << "#*#*BACKUP COMPLETE*#*#" << endl;
	return 0;
}
int BackerUpMoverUtil::writeBackup(BackerUpProfile profile)
{
	/*string pathToBackup;
	for (int i = 0; i < profile.getNoOfBackupPaths(); i++) {
		pathToBackup = profile.getBackUpPath(i);
		makeBackup(pathToBackup, profile.getDestination());
	}*/
	for (list<BackerUpProfile::BackupLocation>::iterator itr = profile.backupInputList.begin(); itr != profile.backupInputList.end(); itr++) {
		makeBackup(itr->path, profile.getDestination());
	}
	return 0;
}
void BackerUpMoverUtil::printDirectory(string path)
{
	std::filesystem::path currentDir(path);
	for (auto const& dirFile : fs::directory_iterator(currentDir)) {
		if (fs::is_directory(dirFile)) { cout << "DIR:" << dirFile << endl; }
		else { cout << dirFile << endl; }
	}
}
