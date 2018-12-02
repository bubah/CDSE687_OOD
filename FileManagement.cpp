///////////////////////////////////////////////////////////////////////////////
// FileManagement.cpp - Application interface to the filesystem operations			
// ver 2.0																			
// Language:    C++, Visual Studio 2017												
// Platform:    Microsoft Surface Pro 4, Windows 10									
// Application: Project 1, Single Node Map/Reduce Program							
// Author:      Bubah Conteh, Syracuse University CSE 687 - 
//				Object Oriented Design	
//              bconteh@syr.edu														
///////////////////////////////////////////////////////////////////////////////

#include "filemanagement.h"
#include "directory_management.h"
#include "filemanagement_exception.h"
#include <boost/log/trivial.hpp>

FileManagement::FileManagement() {}

FileManagement::FileManagement(const std::string& in_path, const std::string& t_path, 
	const std::string& out_path, const std::string& dll_path){}

std::string FileManagement::ReadLineFromFile(const std::string& filename,
	boost::filesystem::ifstream& ifs) {
	BOOST_LOG_TRIVIAL(info) << "Now reading input directory from file '" 
		<< filename << "'" << "\n";

	boost::filesystem::path inputfile_path(filename);

	std::string record{ "" }; // Declare std::string variable for storing file content

	try {
		if (!exists(inputfile_path)) {
			throw FileDoesNotExist();
		} else {
			std::string temp_string;
			getline(ifs, temp_string);
			record += (temp_string + " ");
		}
	} catch (FileDoesNotExist &error1) {
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << filename << "'. "
			<< error1.what() << std::endl;
	}
	return record;
}

std::string FileManagement::ReadWholeFile(std::string filename,
	boost::filesystem::path tempDir) {

	BOOST_LOG_TRIVIAL(info) << "Now reading interm directory from file '" 
		<< filename << "'" << "\n";

	boost::filesystem::path tmp(tempDir);
	std::string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(tmp)) {// if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		} else {//else read content from file line
			std::string tempString{ "" };
			boost::filesystem::ifstream ifs{ tmp.append(filename) };

			while (getline(ifs, tempString)) {
				record += (tempString + " ");
			}
		}
	} catch (FileDoesNotExist &error1) //
	{
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << filename << "'. "
			<< error1.what() << std::endl;
	}

	return record;
}

void FileManagement::WriteToTempFile(const std::string& filename, 
	std::vector<std::string> file_content, boost::filesystem::path tempDir){

	boost::filesystem::path tmp(tempDir); // creates a path using directory string

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		} else { //else print content to file
			tmp.append(filename);
			boost::filesystem::ofstream ofs{ tmp, std::ios_base::trunc }; // Clears content in file
			ofs.close(); // Close file

			for (std::string &word : file_content) {
				ofs.open(tmp, std::ios_base::app);
				ofs << word << '\n';
				ofs.close();
			}
		}
	} catch (FileDoesNotExist &error1) { //
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename 
			<< "'. " << error1.what() << std::endl;
	}
}

void FileManagement::WriteToTempFile(const std::string& filename, 
	std::vector<std::pair<std::string,std::string>>& file_content,
	boost::filesystem::path tempDir) {

	boost::filesystem::path tmp(tempDir);

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		} else { //else print content to file
			tmp.append(filename);
			for (std::pair<std::string, std::string> &w : file_content) {
				boost::filesystem::ofstream ofs(tmp, std::ios_base::app);
				ofs << w.first << "," << w.second << '\n';
				ofs.close();
			}
		}
	} catch (FileDoesNotExist &error1) {
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename << "'. "
			<< error1.what() << std::endl;
	}
}

void FileManagement::WriteToOutputFile(const std::string& filename, 
	const std::string& file_content, boost::filesystem::path outputDir) {
	BOOST_LOG_TRIVIAL(info) << "Now writing to output directory to file '" << filename
		<< "'" << "\n";

	// Make a copy to avoid overwriting the private data member
	boost::filesystem::path tmp(outputDir);

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		} else { //else print content to file
		
			tmp.append(filename);
			boost::filesystem::ofstream ofs{ tmp, std::ios_base::app };
			ofs << file_content << '\n';
			ofs.close();
		}
	} catch (FileDoesNotExist &error1) { //
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename << "'. "
			<< error1.what() << std::endl;
	}
}

void FileManagement::WriteToOutputFile(const std::string& filename,
	std::vector< std::pair<std::string, std::string> >& file_content,
	boost::filesystem::path outputDir){

	BOOST_LOG_TRIVIAL(info) << "Now writing to output directory to file '"
		<< filename << "'" << "\n";

	boost::filesystem::path tmp(outputDir);

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		} else { //else print content to file
			tmp.append(filename);
			for (auto &w : file_content) {
				boost::filesystem::ofstream ofs{ tmp, std::ios_base::app };
				ofs << w.first << ": " << w.second << '\n';
				ofs.close();
			}
		}
	} catch (FileDoesNotExist &error1) {
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename << "'. "
			<< error1.what() << std::endl;
	}
}

const size_t FileManagement::CountFilesInputDir(DirectoryManagement dm) {
	size_t numberOfFiles = 0; // Initialize variable

	while ((dm.GetInputFilename() != "-1")) { // iterate through directory and count files
		numberOfFiles++;
		dm.IncrementInputFilePointer();
	}

	return numberOfFiles;
}

void FileManagement::SetFileAttributes(DirectoryManagement dm) {

	size_t numOfFiles = CountFilesInputDir(dm); // Number of files in dir

	// create a file_attribute object and push to vector
	for (int count = 0; count < numOfFiles; count++) {
		File_attribute file_attribute_obj;
		file_attribute_obj.file_name_ = dm.GetInputFilename();

		list_of_input_dir_files_.push_back(file_attribute_obj);
		dm.IncrementInputFilePointer();
	}

	SetFileDetails(); // Set file start/end bound and number of lines in each file
}

void FileManagement::SetFileBounds(File_attribute& file) {
	std::string line; // temporary variable hold line of file data
	static size_t file_start_bound = 0; // initialize start bound to zero
	file_start_bound++; // increment to first line
	size_t line_count = 0; // line counter initialized

	std::ifstream fin(file.file_name_);

	// Increment line counter
	while (getline(fin, line)) {
		line_count++;
	}

	file.number_of_lines_ = line_count; // set number of file lines
	file.file_start_bound_ = file_start_bound; // set start bound
	file.file_end_bound_ = file_start_bound + (line_count - 1); // set end bound
	file_start_bound = file.file_end_bound_; // set start bound to last line of current file
}

void FileManagement::SetFileDetails() {
	// Loop through file attribute and set start/end bounds
	for (File_attribute &file : list_of_input_dir_files_)
		SetFileBounds(file);
}

void FileManagement::SetInputDir_total_lines() {
	for (File_attribute &fileIndex : list_of_input_dir_files_) {
		total_file_lines_input_dir += fileIndex.number_of_lines_;
	}
}

size_t FileManagement::GetInputDirLines() {
	return total_file_lines_input_dir;
}