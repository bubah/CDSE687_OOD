#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace boost::filesystem;

path me;

class FileManagement
{
public:
	FileManagement(); //Default Constructor
	//void createInputDir(path); //creates the input directory
	//void createTmpDir(path tmpDir);	//creates the temporary directory
	//void createOutputDir(path outputDir);
	void createFile(string);
	void writeToInputFile(string inputFile);
	string readFromInputFile(string inputFile);
	void writeToTmpFile(string tmpFile);
	string readFromTmpFile(string tmpFile);
	void writeToOutputFile(string tmpFile);
	string readFromOutputFile(string tmpFile);

private:
	path inputDir;
	path tmpDir;
	path outputDir;

};

#endif // !FILEMANAGEMENT_H

