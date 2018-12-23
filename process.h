///////////////////////////////////////////////////////////////////////////////
//        File: process.h
// Description: Defines the number of partitions for the Map class and 
//              associated functionality
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Rob Hardisty, rlhardis@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

#include "directory_management.h"
#include "filemanagement.h"

class Process {
public:
	virtual void SpawnProcess() = 0;

	virtual int SpawnProcess(DirectoryManagement &dmobj, FileManagement& fmobj,
		const int num_partitions, std::vector<std::string> files);

private:
	const std::string process_name_;
};

#endif // PROCESS_H
