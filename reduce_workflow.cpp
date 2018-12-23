///////////////////////////////////////////////////////////////////////////////
//        File: reduce_workflow.cpp
// Description: Entry point to reduce phase from controller
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <boost/log/trivial.hpp>

#include <string>
#include <vector>
#include<sstream>

#include "directory_management.h"
#include "filemanagement.h"
#include "reduce_process.h"

int main(int argc, char *argv[]) {
	BOOST_LOG_TRIVIAL(info) << " Now running in Reduce proc ";
	const std::string kInputDir = argv[0]; // Input directory
	const std::string kTempDir = argv[1]; // temp directory
	const std::string kOutputDir = argv[2]; // output directory
	const std::string kDllDir = argv[3]; // dll directory
	const int num_reduce_processes = std::stoi(argv[4]);
	const int reduce_partition_num = std::stoi(argv[5]); // controller assigned partition number
	int num_map_processes = argc - 6;
	std::vector<std::string> map_id;
	for (int idx = 0; idx < num_map_processes; idx++) {
		map_id.push_back(argv[6 + idx]);
	}
	FileManagement fmobj;
	DirectoryManagement dmobj(kInputDir, kTempDir, kOutputDir, kDllDir);
	ReduceProcess reduce_object;
	reduce_object.SpawnProcess(dmobj, fmobj, num_reduce_processes, 
                               reduce_partition_num, map_id);
    BOOST_LOG_TRIVIAL(info) << "Reduce workflow complete!";
	return 0;
}
