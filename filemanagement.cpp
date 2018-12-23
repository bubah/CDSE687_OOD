///////////////////////////////////////////////////////////////////////////////
//        File: filemanagement.cpp
// Description: Implementation of filesystem Utility class 
//    Language: Visual C++
//    Platform: Microsoft Surface Pro Pro Windows 10
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include <boost/log/trivial.hpp>

#include <Windows.h>
#include <iostream>

#include "filemanagement.h"
#include "generatefilename.h"
#include "partition.h"

typedef boost::filesystem::ofstream BoostOFS;

FileManagement::FileManagement() {}

// Reads a line of file data at a time
std::string FileManagement::ReadLineFromFile(
	const std::string &filename,
	BoostIFS *ifs) {
	BoostPath inputfile_path(filename);

	// Declare std::string variable for storing file content
	std::string record{ "" };
	try {
		if (!exists(inputfile_path)) {
			throw FileDoesNotExist();
		} else {
			std::string temp_string; // temp string to store line of ile data
			getline(*ifs, temp_string);
			record += (temp_string + " "); // concatenate file data to record
		}
	} catch (FileDoesNotExist &error) {
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << filename
			<< "'. " << error.what() << std::endl;
	}
	return record;
}

// reads all lines of a file at once
std::string FileManagement::ReadWholeFile(
	const std::string &filename,
	const BoostPath &temp_dir) {
	boost::filesystem::path tmp(temp_dir);

	// Declare string variable for storing file content
	std::string record{ "" };

	try {
		if (!exists(tmp)) {// if file does not exist log error to console
			throw FileDoesNotExist();
		} else {//else read content from file line
			std::string temp_string{ "" };
			BoostIFS ifs{ tmp.append(filename) };
			while (getline(ifs, temp_string)) {
				record += (temp_string + "\n");
			}
		}
	} catch (FileDoesNotExist &error) {
		BOOST_LOG_TRIVIAL(error) << "error reading from file '"
			<< filename << "'. " << error.what() << std::endl;
	}
	return record;
}

// appends data to file in temp directory 
void FileManagement::WriteToTempFile(
	const std::string &filename,
	const VectorStrStr &file_content,
	const BoostPath &temp_dir, const int num_partitions) const {
	Partition partitionObj(num_partitions); // partition object

	// if file does not exist throw error and abort program/process
	try {
		if (!exists(temp_dir)) { // If file does not exisst log exception
			throw FileDoesNotExist();
		} else { //else write content to file
			for (const std::pair<std::string, std::string> &curr_line
				: file_content) {
				BoostPath tempFile(temp_dir); // temp file path

				//return int based on hashkey for use in filename
				int part = partitionObj.GetPartition(curr_line.first);

				// Create a file name based on process id and hashkey value
				std::string config_filename = GenerateFileName(filename, part);
				tempFile.append(config_filename); // append filename to path

				// Create file and append key/value data
				BoostOFS ofs(tempFile, std::ios_base::app);
				ofs << curr_line.first << "," << curr_line.second << '\n';
				ofs.close(); // close file
			}
		}
	} catch (FileDoesNotExist &error) {
		BOOST_LOG_TRIVIAL(error) << "error writing to file" << filename << ". "
			<< error.what() << std::endl;
	}
}

void FileManagement::WriteToOutputFile(
	const std::string &filename,
	const std::string &file_content,
	const BoostPath &output_dir) const {
	BOOST_LOG_TRIVIAL(info) << "Now writing to output directory to file '"
		<< filename << "'";

	// Make a copy to avoid overwriting the private data member
	BoostPath tmp(output_dir);

	try {
		if (!exists(tmp)) { // if file does not exist throw log error
			throw FileDoesNotExist();
		} else { //else print content to file
			tmp.append(filename);
			BoostOFS ofs{ tmp, std::ios_base::app };
			ofs << file_content << '\n';
			ofs.close();
		}
	} catch (FileDoesNotExist &error) { //
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" <<
			filename << "'. " << error.what() << std::endl;
	}
}

void FileManagement::WriteToOutputFile(
	const std::string &filename,
	MapStrStr &content,
	const BoostPath &output_dir) const {
	BoostPath tmp(output_dir);
	try {
		if (!exists(tmp)) { // if file does not exist log error to console
			throw FileDoesNotExist();
		} else { //else print content to file
			tmp.append(filename);
      for (MapStrStr::const_iterator itr = content.begin(); 
		  itr != content.end(); ++itr) {
				BoostPath temp_file(output_dir); // temp file path
				temp_file.append( GenerateFileName( filename ) ); // append filename to path
				BoostOFS ofs{ temp_file, std::ios_base::app };
        ofs << itr->first << ": " << itr->second << "\n";
				ofs.close();
      }
		}
	} catch (FileDoesNotExist &error) {
		BOOST_LOG_TRIVIAL(error) << "error writing to file '"
			<< filename << "'. " << error.what() << std::endl;
	}
}
