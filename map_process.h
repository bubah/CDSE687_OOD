///////////////////////////////////////////////////////////////////////////////
//        File: map_process.h
// Description: Runs the logic for the map phase 
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef MAP_PROCESS_H
#define MAP_PROCESS_H

#include <windows.h>

#include <iostream>
#include <string>

#include "directory_management.h"
#include "filemanagement.h"
#include "process.h"

typedef std::function< void() > FNPTRVOID; // points to function with no param

class MapProcess : public Process {
public:
	virtual void SpawnProcess();
	int StartPhase(
        DirectoryManagement &dmobj, 
        FileManagement &fmobj,
		const int numberOfPartition, 
        std::vector<std::string> &input_files);

	static void MapClientThread(FNPTRVOID func);
};
#endif
