///////////////////////////////////////////////////////////////////
// Executive.cpp - Receives all user input and passes it off to 
//				   the Wowrkflow class for processing.
//
// Language: Visual C++
// Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 1, Single Node Map/Reduce Program
// Author: Rob Hardisty
// Syracuse University, CSE 687 - Object Oriented Design
// rlhardis@syr.edu
//
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include "Workflow.h"
#include "Reduce.h"
#include "FileManagement.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
namespace fs = boost::filesystem;

string getUserInput();

void main()
{
	string userInput;
	string strInputPath;
	string strOutputPath;
	string strTempPath;

	bool isFalse = true;

	// Prompt the user for the INPUT directory
	cout << "\nEnter the input directory: ";
	strInputPath = getUserInput();

	// Prompt the user for the OUTPUT directory
	cout << "\nEnter the output directory: ";
	strOutputPath = getUserInput();

	// Prompt the user for the TEMPORARY directory
	cout << "\nEnter the temporary directory: ";
	strTempPath = getUserInput();

	// Kick off the workflow for data processing
	Workflow wf(strInputPath, strOutputPath, strTempPath);
}


string getUserInput()
{

	string userInput;
	bool isFalse = true;

	while (isFalse)
	{
		getline(cin, userInput);
		fs::path pathInput(userInput);

		if (!fs::exists(userInput))
		{
			cout << "Directory does not exist. Please re-enter: ";
			isFalse = true;
		}
		else
			isFalse = false;
	}

	return userInput;
}

/*int main() {
	FileManagement fm("C:\\testInput", "C:\\testTemp", "C:\\testOutput");
	cout << fm.getInputFileName() << endl;
	cout << fm.readFromTmpFile(fm.getTmpFileName()) << endl;
	fm.writeToInputFile("john", "him");
}*/