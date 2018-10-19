#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
namespace fs = boost::filesystem;


class FileManagement
{
public:
	FileManagement(); //Default Constructor
	FileManagement(string, string = "", string = ""); //Constructor with 3 params
	FileManagement(FileManagement &&) = delete;  //Disable Move constructor
	//void createInputDir(path); //creates the input directory
	//void createTmpDir(path tmpDir);	//creates the temporary directory
	//void createOutputDir(path outputDir);
	void writeToInputFile(string inputFile, string content);
	string readFromInputFile(string);
	//void writeToTmpFile(string tmpFile);
	//string readFromTmpFile(string tmpFile);
	//void writeToOutputFile(string tmpFile);
	//string readFromOutputFile(string tmpFile);

private:
	fs::path inputDir;
	fs::path tmpDir;
	fs::path outputDir;
	void createFile(string); //create a file

};

#endif // !FILEMANAGEMENT_H

