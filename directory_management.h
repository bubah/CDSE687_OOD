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

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <string>

class DirectoryManagement {
public:
	DirectoryManagement(); //Default Constructor
	DirectoryManagement(
	std::string input_d, //Constructor with 3 params
	std::string temp_d,
	std::string output_d,
	std::string dll_d);

	DirectoryManagement(const DirectoryManagement& dm); // copy constructor
	DirectoryManagement& operator=(const DirectoryManagement& dm); // copy assignment

	std::string GetTempFilename();  //gets name of file directory iterator is currently pointing to.
	std::string GetInputFilename();
	std::string GetOutputFilename();

	boost::filesystem::path GetInputDir() const;
	boost::filesystem::path GetTempDir() const;
	boost::filesystem::path GetOutputDir() const;
	boost::filesystem::path GetDllDir() const;

	const boost::filesystem::directory_iterator GetInputIterator() const;
	const boost::filesystem::directory_iterator GetTempIterator() const;
	const boost::filesystem::directory_iterator GetOutputIterator() const;

	void IncrementInputFilePointer();
	void IncrementTmpFilePointer();
	void IncrementOutputFilePointer();

	std::string GetFilenameFromPath(const std::string &filename_and_path);
	bool IsHidden(const std::string&);
private:
	boost::filesystem::path input_dir_;
	boost::filesystem::path temp_dir_;
	boost::filesystem::path output_dir_;
	boost::filesystem::path dll_dir_;
	boost::filesystem::directory_iterator input_dir_itr{ input_dir_ };  //iterates through files in directory
	boost::filesystem::directory_iterator temp_dir_itr{ temp_dir_ };
	boost::filesystem::directory_iterator output_dir_itr{ output_dir_ };
};

#endif //DIRECTORY_MANAGEMENT_H
