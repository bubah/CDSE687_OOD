///////////////////////////////////////////////////////////////////////////////
//        File: reduce_process.h
// Description: Implementaton file for map_process 
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef REDUCE_PROCESS_H
#define REDUCE_PROCESS_H

#include <windows.h>
#include <iostream>
#include <string>

#include "directory_management.h"
#include "filemanagement.h"
#include "process.h"

typedef std::function< void() > FNPTRVOID; // points to function with no param

class ReduceProcess : public Process {
public:
	ReduceProcess();
	void SpawnProcess();
	int SpawnProcess(
		DirectoryManagement &dmobj,
		FileManagement& fmobj,
		const int kNumPartitions,
		std::vector<std::string> &input_files);
	int SpawnProcess(
		DirectoryManagement &dmobj,
		FileManagement& fmobj,
		const int kNumPartitions,
		const int kReducePartitionNum,
		std::vector<std::string> mapID);
	static void ReduceClientThread(FNPTRVOID func);
    const std::string &kLocalHostIP = "127.0.0.1";
    const int kLocalHostPort = 54;
};

#endif // REDUCE_PROCESS_H
