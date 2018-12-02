#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

///////////////////////////////////////////////////////////////////////////////
// fileManagement.h - Abstracts away the details of the file system				
// ver 2.0																		
// Language:    C++, Visual Studio 2017											
// Platform:    Microsoft Surface Pro 4, Windows 10								
// Application: Project 1, Single Node Map/Reduce Program						
// Author:      Bubah Conteh, Syracuse University CSE 687 - 
//				Object Oriented Design
//              bconteh@syr.edu														
///////////////////////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "directory_management.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct File_attribute {
	size_t number_of_lines_; // Number of lines in file
	std::string file_name_;
	size_t file_start_bound_; // File start Line with respect to all lines in directory
	size_t file_end_bound_; // File end Line with respect to all lines in directory 
};

class FileManagement {

public:

	FileManagement(); //Default Constructor

	FileManagement(const std::string& input_d, const std::string& temp_d, const std::string& out_d,
		const std::string& dll_d);

	std::string ReadLineFromFile(const std::string &inputFileName,
		boost::filesystem::ifstream& ifs);

	std::string ReadWholeFile(std::string tmp_filename,
		boost::filesystem::path tempDir);

	void WriteToTempFile(const std::string& filename, 
		std::vector<std::string> file_content, boost::filesystem::path tempDir);

	void WriteToTempFile(const std::string& filename, std::vector<std::pair<std::string,
		std::string>>& file_content, boost::filesystem::path tempDir);

	void WriteToOutputFile(const std::string& filename, 
		std::vector < std::pair<std::string, std::string> >& filepath, 
		boost::filesystem::path outputDir);

	void WriteToOutputFile(const std::string& filename, const std::string& file_content, 
		boost::filesystem::path outputpDir);

	void SetFileAttributes(DirectoryManagement dm);

	void SetInputDir_total_lines();

	size_t GetInputDirLines();

private:
	std::vector<File_attribute> list_of_input_dir_files_;
	size_t total_file_lines_input_dir;
	const size_t CountFilesInputDir(DirectoryManagement dm);
	void SetFileBounds(File_attribute& file);
	void SetFileDetails();
};

#endif
