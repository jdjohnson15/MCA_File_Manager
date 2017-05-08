// MCA_FileManager.cpp : Defines the entry point for the console application.
//


#include "boost/filesystem.hpp"
#include <iostream>
#include <sys/stat.h>
#include <string>

using namespace boost::filesystem;
using namespace std;

/*
baker
butcher
child
ee
farmer
guard
librarian
miner
priest
smith
warrior
*/

std::string roles[20] = {
	".\/male\/Baker",
	".\/male\/Butcher",
	".\/male\/Child",
	".\/male\/Farmer",
	".\/male\/Guard",
	".\/male\/Librarian",
	".\/male\/Miner",
	".\/male\/Priest",
	".\/male\/Smith",
	".\/male\/Warrior",
	".\/female\/Baker",
	".\/female\/Butcher",
	".\/female\/Child",
	".\/female\/Farmer",
	".\/female\/Guard",
	".\/female\/Librarian",
	".\/female\/Miner",
	".\/female\/Priest",
	".\/female\/Smith",
	".\/female\/Warrior"
};

int main(int argc, char *argv[])
{
	path female("./female");
	if (!exists(female)) {
		create_directory(female);
	}
	path male("./male");
	if (!exists(male)) {
		create_directory(male);
	}
	//make array of references for the 22 directories for the 22 roles
	path* p[22];
	for (int i = 0; i < 20; i++) {
		p[i] = new path(roles[i]);
		if (!exists(*p[i])) {
			if (create_directory(*p[i]) != 0) {
				cout << "something went wrong" << endl;
			}
		}
			create_directory(*p[i]);
	}

	int numberOfFiles = 0;
	char* destination = "skins";//argv[0];
	printf("Beginning file renaming.\nPlacing renamed files in %s\n", destination);

	
	//go through each directory and handle the files
	for (int i = 0; i < 20; i++) {

		//null directory_iterator to designate end of directory
		directory_iterator end_itr;

		string gender;
		int dir_buffer = 0;

		//if i is less than 11, it's a male folder. Otherwise it's female
		//this also denotes the directory buffer size
		if (i < 10) {
			gender = 'M';
			dir_buffer = 7;
		}
		else {
			gender = 'F';
			dir_buffer = 9;
		}

		int skinNumber = 1;
		//iterate to each file within the directory
		for (directory_iterator itr(*p[i]); itr != end_itr; ++itr)
		{
			string oldpath = itr->path().string();

			//newpath = <destionation_dir></><role><gender M/F><skinNumber, 1 terminating>
			string newpath = destination;
			newpath.append("\/");
			newpath.append(roles[i], dir_buffer, roles[i].length() - dir_buffer);
			newpath.append(gender);
			newpath.append(to_string(skinNumber));
			newpath.append(".png");

			//handle failure
			int failure = rename(oldpath.c_str(), newpath.c_str());
			if (failure != 0) {
				cout << newpath << " failed to write -- error code " << failure << endl;
			}
			else {
				cout << newpath << failure << endl;
				++skinNumber;
				++numberOfFiles;
			}
		}
	}
	printf("Process complete. Created %i files for MCA\n", numberOfFiles);
	system("pause");
    return 0;
}

