///////////////////////////////////////////////////////////////////////////////
//        File: directory_management.cpp
// Description: Abstracts away the details of the file system
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Multi Node Map/Reduce Program
//      Author: Rob Hardisty, rlhardis@syr.edu/Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef DIRECTORY_MANAGEMENT
#define DIRECTORY_MANAGEMENT

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <string>

typedef boost::filesystem::path BoostPath;
typedef boost::filesystem::directory_iterator BoostDirIterator;

class DirectoryManagement {
public:
	DirectoryManagement(); //Default Constructor

	DirectoryManagement(
		const std::string &input_d, //Constructor with 3 params
		const std::string &temp_d,
		const std::string &output_d,
		const std::string &dll_d);

	DirectoryManagement(const DirectoryManagement &dmobj); // copy constr
	DirectoryManagement& operator=(const DirectoryManagement &dmobj); // copy assignment

	// Gets name of file directory iterator is currently pointing to.
	std::string GetTempFilename();
	std::string GetInputFilename();
	std::string GetOutputFilename();

	// Getters for file paths
	const BoostPath GetInputDir() const;
	const BoostPath GetTempDir() const;
	const BoostPath GetOutputDir() const;
	const BoostPath GetDllDir() const;

	// Getter for the file iterators
	const BoostDirIterator GetInputIterator() const;
	const BoostDirIterator GetTempIterator() const;

	// Increments the file pointer to the file list
	void IncrementInputFilePointer();
	void IncrementTmpFilePointer();

	// Breaks out the filename from the path
	std::string GetFilenameFromPath(std::string &filename_and_path) const;
	bool IsHidden(const std::string &filename);

private:
	// Default filenames
	const std::string kdefault_filename_temp_ = "temp";
	const std::string kdefault_filename_output_ = "output";

	// Keeps tracks of the various directories
	BoostPath input_dir_;
	BoostPath temp_dir_;
	BoostPath output_dir_;
	BoostPath dll_dir_;

	// Iterator points to the next file in the list
	BoostDirIterator input_dir_itr_{ input_dir_ };
	BoostDirIterator temp_dir_itr_{ temp_dir_ };
	BoostDirIterator output_dir_itr_{ output_dir_ };
};
#endif //DIRECTORY_MANAGEMENT_H
