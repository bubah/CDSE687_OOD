#ifndef DIRECTORY_MANAGEMENT
#define DIRECTORY_MANAGEMENT

//////////////////////////////////////////////////////////////////////////////////////
// directory_management.h - Abstracts away the details of the file system			//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 1, Single Node Map/Reduce Program							//
// Author:      Bubah Conteh, Syracuse University CSE 687 - Object Oriented Design	//
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

class DirectoryManagement {
public:
	DirectoryManagement(); //Default Constructor
	DirectoryManagement(
		std::string input_d, //Constructor with 3 params
		std::string temp_d,
		std::string output_d,
		std::string dll_d);

	std::string GetTempFilename();  //gets name of file directory iterator is currently pointing to.
	std::string GetInputFilename();
	std::string GetOutputFilename();

	boost::filesystem::path GetInputDir();
	boost::filesystem::path GetTempDir();
	boost::filesystem::path GetOutputDir();
	boost::filesystem::path GetDllDir();

	const boost::filesystem::directory_iterator GetInputIterator();
	const boost::filesystem::directory_iterator GetTempIterator();
	const boost::filesystem::directory_iterator GetOutputIterator();

	void IncrementInputFilePointer();
	void IncrementTmpFilePointer();
	void IncrementOutputFilePointer();

	std::string GetFilenameFromPath(std::string filename_and_path);
	bool IsHidden(std::string);
private:
	const boost::filesystem::path input_dir;
	const boost::filesystem::path temp_dir;
	const boost::filesystem::path output_dir;
	const boost::filesystem::path dll_dir;
	boost::filesystem::directory_iterator input_dir_itr{ input_dir };  //iterates through files in directory
	boost::filesystem::directory_iterator temp_dir_itr{ temp_dir };
	boost::filesystem::directory_iterator output_dir_itr{ output_dir };
};



#endif //DIRECTORY_MANAGEMENT_H
