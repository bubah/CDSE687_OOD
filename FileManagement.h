#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

//////////////////////////////////////////////////////////////////////////////////////
// fileManagement.h - Abstracts away the details of the file system					//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "directory_management.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileManagement {

public:

	FileManagement(); //Default Constructor

	FileManagement(std::string input_d, std::string temp_d, std::string out_d, std::string dll_d);

	std::string ReadFromInputFile(std::string inputFileName, boost::filesystem::ifstream& ifs);

	std::string ReadFromTempFile(std::string tmp_filename, boost::filesystem::path tempDir);

	void WriteToTempFile(std::string filename, std::vector<std::string> file_content, boost::filesystem::path tempDir);

	void WriteToTempFile(std::string filename, std::vector<std::pair<std::string,std::string>> file_content, boost::filesystem::path tempDir);

	void WriteToOutputFile(std::string filename, std::vector < std::pair<std::string, std::string> > filepath, boost::filesystem::path outputDir);

	void WriteToOutputFile(std::string filename, std::string file_content, boost::filesystem::path outputpDir);

	//bool IsHidden(std::string);

private:

};

#endif
