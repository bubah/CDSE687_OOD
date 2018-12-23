///////////////////////////////////////////////////////////////////////////////
//        File: directory_management.h
// Description: Abstracts away the details of the file system
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Multi Node Map/Reduce Program
//      Author: Rob Hardisty, rlhardis@syr.edu/Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#include <boost/log/trivial.hpp>

#include "directory_management.h"
#include "filemanagement_exception.h"

DirectoryManagement::DirectoryManagement() {
	BOOST_LOG_TRIVIAL(info) << "DirectoryManagement::DirectoryManagement()...";
}

DirectoryManagement::DirectoryManagement(
	const std::string &inpath,
	const std::string &tmppath,
	const std::string &outpath,
	const std::string &dllpath)
	:input_dir_{ inpath },
	temp_dir_{ tmppath },
	output_dir_{ outpath },
	dll_dir_{ dllpath }{

	BOOST_LOG_TRIVIAL(info) << "DirectoryManagement::DirectoryManagement("
		"string, string, string, string)...";
}

DirectoryManagement::DirectoryManagement(const DirectoryManagement& dmobj)
	: input_dir_{ dmobj.GetInputDir() },
	temp_dir_{ dmobj.GetTempDir() },
	output_dir_{ dmobj.GetOutputDir() },
	dll_dir_{ dmobj.GetDllDir() },
	input_dir_itr_{ dmobj.GetInputDir() }{}

DirectoryManagement&
DirectoryManagement::operator=(const DirectoryManagement& dmobj) {
	if (this == &dmobj) return *this;
	input_dir_ = dmobj.GetInputDir();
	temp_dir_ = dmobj.GetTempDir();
	output_dir_ = dmobj.GetOutputDir();
	dll_dir_ = dmobj.GetDllDir();
	return *this;
} // copy assignment

// Gets name of file directory iterator is currently pointing to.
std::string DirectoryManagement::GetTempFilename() {
	if (temp_dir_itr_ == BoostDirIterator{}) {
		return kdefault_filename_temp_;
	}

	BoostPath temp_filepath{ *temp_dir_itr_ };

	// If this is a hidden file, ignore it and increment the file pointer
	if (IsHidden(temp_filepath.filename().string())) {
		IncrementTmpFilePointer();

		if (temp_dir_itr_ == BoostDirIterator{})

			return kdefault_filename_temp_;

		BoostPath temp_filepath{ *temp_dir_itr_ };
	}
	return kdefault_filename_temp_;
}

// Returns the current filename of the file pointed to by the iterator
std::string DirectoryManagement::GetInputFilename() {
	if (input_dir_itr_ == BoostDirIterator{}) {
		return "-1";
	}

	BoostPath inputfilename_path{ *input_dir_itr_ };

	// If this is a hidden file, ignore it and increment the file pointer
	if (IsHidden(inputfilename_path.filename().string())) {
		IncrementInputFilePointer();

		if (input_dir_itr_ == BoostDirIterator{})
			return "-1";
		BoostPath inputfilename_path{ *input_dir_itr_ };
	}

	return inputfilename_path.string();
}

// Returns the current filename of the file pointed to by the iterator
std::string DirectoryManagement::GetOutputFilename() {
	if (output_dir_itr_ == BoostDirIterator{}) {
		return kdefault_filename_output_;
	}

	BoostPath output_filepath{ *output_dir_itr_ };
	return kdefault_filename_output_;
}

std::string DirectoryManagement::GetFilenameFromPath(
	std::string &filename_and_path) const {
	BoostPath p(filename_and_path);
	BoostPath filename = p.filename();
	return filename.string();
}

const BoostPath DirectoryManagement::GetInputDir() const {
	return input_dir_;
}

const BoostPath DirectoryManagement::GetTempDir() const {
	return temp_dir_;
}

const BoostPath DirectoryManagement::GetOutputDir() const {
	return output_dir_;
}

const BoostPath DirectoryManagement::GetDllDir() const {
	return dll_dir_;
}

const BoostDirIterator DirectoryManagement::GetInputIterator() const {
	return input_dir_itr_;
}

const BoostDirIterator DirectoryManagement::GetTempIterator() const {
	return temp_dir_itr_;
}

void DirectoryManagement::IncrementInputFilePointer() {
	input_dir_itr_++;
}

void DirectoryManagement::IncrementTmpFilePointer() {
	temp_dir_itr_++;
}

bool DirectoryManagement::IsHidden(const std::string &filename) {
	return (filename[0] == '.');
}
