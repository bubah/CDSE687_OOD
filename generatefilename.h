///////////////////////////////////////////////////////////////////////////////
//        File: generatefilename.h
// Description: Helper func returns a filename based on naming convention
//    Language: Visual C++
//    Platform: Windows 10 (Visual studion 2017 Community)
// Application: Project 3, Multi Node Map/Reduce Program
//      Author: Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#ifndef GENERATEFILENAME_H
#define GENERATEFILENAME_H

#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

// configures a filename based on process ID and assigned partition
static std::string GenerateFileName(const std::string &filename,
	const int &part) {
	DWORD processID = GetCurrentProcessId();
	return std::to_string(processID) + "_" + filename + "_" + 
		std::to_string(part);
}

// overloads of the function above
static std::string GenerateFileName(const std::string &filename) {
	DWORD processID = GetCurrentProcessId();
	return std::to_string(processID) + "_" + filename;
}

#endif // GENERATEFILENAME_H
