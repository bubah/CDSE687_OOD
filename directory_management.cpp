//////////////////////////////////////////////////////////////////////////////////////
// directory_management.h - Abstracts away the details of the file system			//
// ver 1.0																			//
// Language:    C++, Visual Studio 2017												//
// Platform:    Microsoft Surface Pro 4, Windows 10									//
// Application: Project 2, Single Node Map/Reduce Program							//
// Author:      Rolb Hardisty/Bubah Conteh,                                         //
//              Syracuse University CSE 687 - Object Oriented Design	            //
//              bconteh@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////

#include "directory_management.h"
#include "filemanagement_exception.h"
#include <boost/log/trivial.hpp>

DirectoryManagement::DirectoryManagement() {}

DirectoryManagement::DirectoryManagement(std::string inpath, std::string tmppath, std::string outpath, std::string dllpath)
	:input_dir{ inpath }, temp_dir{ tmppath }, output_dir{ outpath }, dll_dir{ dllpath }{BOOST_LOG_TRIVIAL(info) << "Directory Manager constr" << "\n"; }
	// Returns the current filename of the file pointed to by the iterator

std::string DirectoryManagement::GetTempFilename()  //gets name of file directory iterator is currently pointing to.
{
	if (temp_dir_itr == boost::filesystem::directory_iterator{}) {
		return "temp";
	}

	boost::filesystem::path temp_filepath{ *temp_dir_itr };

	// If this is a hidden file, ignore it and increment the file pointer

	if (IsHidden(temp_filepath.filename().string())) {
		IncrementTmpFilePointer();
		if (temp_dir_itr == boost::filesystem::directory_iterator{})
			return "temp";
		boost::filesystem::path temp_filepath{ *temp_dir_itr };

	}

	return temp_filepath.string();

}

// Returns the current filename of the file pointed to by the iterator

std::string DirectoryManagement::GetInputFilename()
{
	if (input_dir_itr == boost::filesystem::directory_iterator{}) {
		return "-1";
	}

	boost::filesystem::path inputFileName_path{ *input_dir_itr };

	// If this is a hidden file, ignore it and increment the file pointer
	if (IsHidden(inputFileName_path.filename().string())) {
		IncrementInputFilePointer();
		if (input_dir_itr == boost::filesystem::directory_iterator{})
			return "-1";
		boost::filesystem::path inputFileName_Path{ *input_dir_itr };

	}

	return inputFileName_path.string();

}// Returns the current filename of the file pointed to by the iterator

std::string DirectoryManagement::GetOutputFilename()
{
	if (output_dir_itr == boost::filesystem::directory_iterator{}) {
		return "output";
	}
	boost::filesystem::path output_filepath{ *output_dir_itr };

	// If this is a hidden file, ignore it and increment the file pointer

	if (IsHidden(output_filepath.filename().string())) {

		IncrementOutputFilePointer();
		if (output_dir_itr == boost::filesystem::directory_iterator{})
			return "output";

		boost::filesystem::path output_filepath{ *output_dir_itr };
	}

	return output_filepath.string();
}



std::string DirectoryManagement::GetFilenameFromPath(std::string filename_and_path) {

	boost::filesystem::path p(filename_and_path);
	boost::filesystem::path filename = p.filename();
	return filename.string();

}



boost::filesystem::path DirectoryManagement::GetInputDir()
{
	return input_dir;
}



boost::filesystem::path DirectoryManagement::GetTempDir()
{
	return temp_dir;
}



boost::filesystem::path DirectoryManagement::GetOutputDir()
{
	return output_dir;
}



boost::filesystem::path DirectoryManagement::GetDllDir()
{
	return dll_dir;
}



const boost::filesystem::directory_iterator DirectoryManagement::GetInputIterator()
{
	return input_dir_itr;
}

const boost::filesystem::directory_iterator DirectoryManagement::GetTempIterator()
{
	return temp_dir_itr;
}

const boost::filesystem::directory_iterator DirectoryManagement::GetOutputIterator()
{
	return output_dir_itr;
}



void DirectoryManagement::IncrementInputFilePointer()
{
	input_dir_itr++;
}



void DirectoryManagement::IncrementTmpFilePointer()
{
	temp_dir_itr++;
}

void DirectoryManagement::IncrementOutputFilePointer()
{
	output_dir_itr++;
}

bool DirectoryManagement::IsHidden(std::string filename)
{
	return (filename[0] == '.');
}