//////////////////////////////////////////////////////////////////////////////////////
// FileManagement.cpp - Application interface to the filesystem operations			//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////



#include "filemanagement.h"
#include "directory_management.h"
#include "filemanagement_exception.h"
#include <boost/log/trivial.hpp>

FileManagement::FileManagement() {}

FileManagement::FileManagement(std::string in_path, std::string t_path, std::string out_path, std::string dll_path)
{}

std::string FileManagement::ReadFromInputFile(std::string filename, boost::filesystem::ifstream& ifs) {
	BOOST_LOG_TRIVIAL(info) << "Now reading input directory from file '" << filename << "'" << "\n";
	boost::filesystem::path inputfile_path(filename);
	std::string record{ "" }; // Declare std::string variable for storing file content

	try {
		if (!exists(inputfile_path)) {
			throw FileDoesNotExist();
		}else {
			std::string temp_string;
			getline(ifs, temp_string);
			record += (temp_string + " ");
		}
	}
	catch (FileDoesNotExist &error1) {
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << filename << "'. "
			<< error1.what() << std::endl;
	}
	return record;
}



std::string FileManagement::ReadFromTempFile(std::string filename, boost::filesystem::path tempDir) {

	BOOST_LOG_TRIVIAL(info) << "Now reading interm directory from file '" << filename << "'" << "\n";

	//filename = dmobj().GetFilenameFromPath(filename);
	boost::filesystem::path tmp(tempDir);
	std::string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(tmp)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}else //else read content from file line
		{
			std::string tempString{ "" };
			boost::filesystem::ifstream ifs{ tmp.append(filename) };

			while (getline(ifs, tempString)) {
				record += (tempString + " ");
			}
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << filename << "'. "
			<< error1.what() << std::endl;
	}

	return record;
}



void FileManagement::WriteToTempFile(std::string filename, std::vector<std::string> file_content,
	boost::filesystem::path tempDir)
{

	boost::filesystem::path tmp(tempDir);

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		}
		else { //else print content to file
			tmp.append(filename);
			boost::filesystem::ofstream ofs{ tmp, std::ios_base::trunc }; // Clears content in file
			ofs.close(); // Close file

			for (std::string &w : file_content) {
				ofs.open(tmp, std::ios_base::app);
				ofs << w << '\n';
				ofs.close();
			}
		}
	}
	catch (FileDoesNotExist &error1) { //
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename << "'. " << error1.what() << std::endl;
	}
}

void FileManagement::WriteToTempFile(std::string filename, std::vector<std::pair<std::string,std::string>> file_content, boost::filesystem::path tempDir)
{
	DirectoryManagement dmobj();
	//filename = dmobj().GetFilenameFromPath(filename);
	boost::filesystem::path tmp(tempDir);

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		}
		else { //else print content to file
			tmp.append(filename);
			for (std::pair<std::string, std::string> &w : file_content) {
				boost::filesystem::ofstream ofs(tmp, std::ios_base::app);
				ofs << w.first << "," << w.second << '\n';
				ofs.close();
			}
		}
	}
	catch (FileDoesNotExist &error1) { //
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename << "'. " << error1.what() << std::endl;
	}
}

void FileManagement::WriteToOutputFile(std::string filename, std::string file_content, boost::filesystem::path outputDir)
{
	BOOST_LOG_TRIVIAL(info) << "Now writing to output directory to file '" << filename << "'" << "\n";

	// Make a copy to avoid overwriting the private data member
	boost::filesystem::path tmp(outputDir);

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			tmp.append(filename);
			boost::filesystem::ofstream ofs{ tmp, std::ios_base::app };
			ofs << file_content << '\n';
			ofs.close();
		}
	}
	catch (FileDoesNotExist &error1) { //
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename << "'. "
			<< error1.what() << std::endl;
	}
}



void FileManagement::WriteToOutputFile(std::string filename,
	std::vector< std::pair<std::string, std::string> > file_content, boost::filesystem::path outputDir)
{
	//DirectoryManagement dmobj();
	BOOST_LOG_TRIVIAL(info) << "Now writing to output directory to file '" << filename << "'" << "\n";

	boost::filesystem::path tmp(outputDir);

	try {
		if (!exists(tmp)) { // if file does not exist throw error and abort program/process
			throw FileDoesNotExist();
		}
		else { //else print content to file
			tmp.append(filename);
			for (auto &w : file_content) {
				boost::filesystem::ofstream ofs{ tmp, std::ios_base::app };
				ofs << w.first << ": " << w.second << '\n';
				ofs.close();
			}
		}
	}
	catch (FileDoesNotExist &error1) { //
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << filename << "'. "
			<< error1.what() << std::endl;
	}
}
