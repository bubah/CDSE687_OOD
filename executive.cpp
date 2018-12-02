///////////////////////////////////////////////////////////////////////////////
// executive.cpp - Receives all user input and passes it off to 
//	the Wowrkflow class for processing.
//
// Language: Visual C++
// Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 1, Single Node Map/Reduce Program
// Author: Rob Hardisty
// Syracuse University, CSE 687 - Object Oriented Design
// rlhardis@syr.edu
//
///////////////////////////////////////////////////////////////////////////////

#include "workflow.h"
#include <boost/log/trivial.hpp>
#include <iostream>

int main(int argc, char* argv[]) {

	BOOST_LOG_TRIVIAL(info) << "Starting application..." << "\n";
	std::string dir_input;
	std::string dir_temp;
	std::string dir_output;
	std::string dir_dll;

	// Assume empty argument list and use defaults
	if (argc == 1) {
		dir_input = "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\i\\";
		dir_temp = "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\t\\";
		dir_output = "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\o\\";
		dir_dll = "C:\\Users\\conte\\Documents\\MyDLL\\MapReduce.dll";
	} else if (argc == 5) {

		dir_input = argv[1];
		dir_temp = argv[2];
		dir_output = argv[3];
		dir_dll = argv[4];
	} else {

		BOOST_LOG_TRIVIAL(error) << 
		"ERROR evaluating argument list::USAGE: <input_dir> <temp_dir> <output_dir> <dll_dir>";
		return -1;
	}

	BOOST_LOG_TRIVIAL(info) << "Entering workflow...";
	Workflow wf;
	wf.WorkflowMain(dir_input, dir_temp, dir_output, dir_dll);
	return 0;

}