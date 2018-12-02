///////////////////////////////////////////////////////////////////
// Workflow.h - Reduces all data captured in input files from the 
//				map process.
//
// Language: Visual C++
// Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 1, Single Node Map/Reduce Program
// Author: Rob Hardisty
// Syracuse University, CSE 687 - Object Oriented Design
// rlhardis@syr.edu
//
///////////////////////////////////////////////////////////////////

#ifndef WORKFLOW_H
#define WORKFLOW_H
#include <iostream>

#include "directory_management.h"
#include "filemanagement.h"

class Workflow {
public:
	Workflow();
	int WorkflowMain(std::string, std::string, std::string, std::string);

private:
	int MapWorkFlow(DirectoryManagement &dm, FileManagement& fm);
	int ReduceWorkFlow(DirectoryManagement &dm, FileManagement& fm);
	const std::string dir_input;
	const std::string dir_temp;
	const std::string dir_output;
	const std::string dir_dll;

};

#endif
