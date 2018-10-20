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
	void writeToInputFile(string, string);
	string readFromInputFile(string);
	void writeToTmpFile(string, string);
	string readFromTmpFile(string);
	void writeToOutputFile(string, string);
	string readFromOutputFile(string);
	fs::directory_iterator getTmpFileName();  //gets name of file directory iterator is currently pointing to.
	fs::directory_iterator getInputFileName();
	fs::directory_iterator getOutputFileName();

private:
	fs::path inputDir;
	fs::path tmpDir;
	fs::path outputDir;
	static fs::directory_iterator inputDirItr;  //iterates through files in directory
	static fs::directory_iterator tmpDirItr;
	static fs::directory_iterator outputDirItr;
	void createFile(string); //create a file
};

#endif // !FILEMANAGEMENT_H

