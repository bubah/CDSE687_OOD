///////////////////////////////////////////////////////////////////////////////
//        File: filemanagement.cpp
// Description: filesystem Utility class used for read/writes to file
//    Language: Visual C++
//    Platform: Microsoft Surface Pro Pro Windows 10
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <string>
#include <map>
#include <vector>

#include "directory_management.h"
#include "filemanagement_exception.h"

typedef boost::filesystem::path BoostPath;
typedef boost::filesystem::ifstream BoostIFS;
typedef std::map<std::string, std::string> MapStrStr;
typedef std::vector<std::pair<std::string, std::string>> VectorStrStr;

class FileManagement {
public:
	FileManagement(); //Default Constructor

	std::string ReadLineFromFile(
    const std::string &filename,
		BoostIFS *ifs);

	  std::string ReadWholeFile(
    const std::string &tmp_filename,
		const BoostPath &tempDir);

	void WriteToTempFile(
		const std::string &filename,
		const VectorStrStr &file_content,
		const BoostPath &temp_d, 
        int num_partitions) const ;

	void WriteToOutputFile(
		const std::string &filename,
		const std::string &file_content,
		const BoostPath &out_d) const;

	void WriteToOutputFile(
		const std::string &filename,
		MapStrStr &file_content,
		const BoostPath &out_d) const;
};
#endif //FILEMANAGEMENT_H
