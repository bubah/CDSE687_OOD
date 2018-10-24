#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

//////////////////////////////////////////////////////////////////////////////////////
// FileManagement.h - Abstracts away the details of the file system					//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////


#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
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
	FileManagement(); //Default Constructor
	FileManagement(string inputD, string tmpD = "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\TempDir", string outputD = "C:\\CSE687\\Dev\\MapReduce\\MapReduce\\OutputDir"); //Constructor with 3 params
	void writeToInputFile(string inputFileName, string fileContent);
	
	string readFromInputFile(string inputFileName);
	void writeToTmpFile(string tmpFileName, string fileContent);
	void writeToTmpFile(string tmpFileName, vector<string> fileContent);
	string readFromTmpFile(string tmpFileName);
	void writeToOutputFile(string outputFileName, string fileContent);
	void writeToOutputFile(string outputFileName, vector<string> fileContent);
	string readFromOutputFile(string outputFileName);
	string getTmpFileName(void);  //gets name of file directory iterator is currently pointing to.
	string getInputFileName(void);
	string getOutputFileName(void);
	fs::path getInputDir(void);
	void incrementInputFilePointer(void);
	void incrementTmpFilePointer(void);
	void incrementOutputFilePointer(void);

private:
	fs::path inputDir;
	fs::path tmpDir;
	fs::path outputDir;
	fs::directory_iterator inputDirItr{ inputDir };  //iterates through files in directory
	fs::directory_iterator tmpDirItr{ tmpDir };
	fs::directory_iterator outputDirItr{ outputDir };
	//void createFile(string); //create a file
};

#endif // !FILEMANAGEMENT_H

