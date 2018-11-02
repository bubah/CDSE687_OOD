////////////////////////////////////////////////////////////////////////////////
// FileManagement.h - Abstracts away the details of the file system					
// ver 1.0																			
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10								
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////

#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
namespace fs = boost::filesystem;


class FileManagement
{
public:

	// Constructor accepts (3) strings as input
	FileManagement(string inputD, string tmpD = "", string outputD = "");

	// Writes to input file
	void writeToInputFile(string inputFileName, string fileContent);

	// Reads from input file
	string readFromInputFile(string inputFileName);

	// Writes to temp file
	void writeToTmpFile(string tmpFileName, string fileContent);

	// Writes to temp file
	void writeToTmpFile(string tmpFileName, vector<string> fileContent);

	// Reads from temp file
	string readFromTmpFile(string tmpFileName);

	// Recieves stirng data and writes to output file
	void writeToOutputFile(string outputFileName, string fileContent);

	// Recieves vector data and writes to output file
	void writeToOutputFile(string outputFileName, vector< std::pair<string, int> > fileContent);

	// Reads from outoput file
	string readFromOutputFile(string outputFileName);

	// Return file name from temp directory
	string getTmpFileName(void);

	// Return file name from input directory
	string getInputFileName(void);

	// Return file name from output directory
	string getOutputFileName(void);

	// Returns path to input dir
	fs::path getInputDir(void);

	// Returns path to temp dir
	fs::path getTempDir(void);

	// Increments input file pointer
	void incrementInputFilePointer(void);

	// Increments temp file pointer
	void incrementTmpFilePointer(void);

	// Increments output file pointer
	void incrementOutputFilePointer(void);

	// Return true if file is hidden
	bool isHidden(string);

private:

	// Class member data
	fs::path inputDir;
	fs::path tmpDir;
	fs::path outputDir;

	// Directory pointers
	fs::directory_iterator inputDirItr{ inputDir };
	fs::directory_iterator tmpDirItr{ tmpDir };
	fs::directory_iterator outputDirItr{ outputDir };

};

#endif // !FILEMANAGEMENT_H