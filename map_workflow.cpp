///////////////////////////////////////////////////////////////////////////////
//        File: map_workflow.cpp
// Description: Entry point to map phase from controller
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include<sstream>

#include "directory_management.h"
#include "filemanagement.h"
#include "map_process.h"

// Entry point to map process
int main(int argc, char *argv[]) {
	std::string input_dir = argv[0]; // Input directory
	std::string temp_dir = argv[1]; // temp directory
	std::string output_dir = argv[2]; // output directory
	std::string dll_dir = argv[3]; // dll directory
	const int num_reduce_processes = std::stoi(argv[4]);
	const int num_input_files = argc - 5;

	// store input file names from cmd line to string vector
	std::vector<std::string> input_filenames;

	// push input files from cmd line to string vector
	for (int idx = 0; idx < num_input_files; idx++) {
		input_filenames.push_back(argv[5 + idx]);
	}

	// create file and directory objects
	FileManagement file_manager_obj;
	DirectoryManagement dir_mannager_obj(input_dir, temp_dir, output_dir,
		dll_dir);

	// spawn map phase
	MapProcess map_object;
	map_object.StartPhase(dir_mannager_obj, file_manager_obj,
		num_reduce_processes, input_filenames);

	return 0;
}
