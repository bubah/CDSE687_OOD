///////////////////////////////////////////////////////////////////////////////
//        File: filemanagement_exception.h
// Description: Throws and exception on file reading errors
//    Language: Visual C++
//    Platform: Windows 10 (Visual studion 2017 Community)
// Application: Project 3, Multi Node Map/Reduce Program
//      Author: Bubah Conteh, bconteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef FILEMANAGEMENT_EXCEPTION_H
#define FILEMANAGEMENT_EXCEPTION_H

#include <stdexcept>

/* Class inherits from runtime_error class. This class is used to handle file
read errors in the Filemanagement Class */
class FileDoesNotExist : public std::runtime_error {
public:
	FileDoesNotExist() : std::runtime_error("File Does not exist") {}
};
#endif // FILEMANAGEMENT_EXCEPTION_H
