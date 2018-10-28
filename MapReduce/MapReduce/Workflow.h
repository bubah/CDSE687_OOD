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
using std::string;

class Workflow
{
public:
	Workflow(string, string, string);

private:
	string dirInput;
	string dirOutput;
	string dirTemp;
};

#endif