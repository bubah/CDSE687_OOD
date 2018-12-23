///////////////////////////////////////////////////////////////////////////////
//        File: process.cpp
// Description: Defines the number of partitions for the Map class and 
//              associated functionality
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Rob Hardisty, rlhardis@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <boost/log/trivial.hpp>

#include <iostream>
#include <Windows.h>
#include <stdio.h>

#include "process.h"

int Process::SpawnProcess(DirectoryManagement &dm, FileManagement& fm,
	const int numberOfPartition, std::vector<std::string> files) {
	BOOST_LOG_TRIVIAL(info) << "Initiating Process: " << process_name_;
	return 0;
}
