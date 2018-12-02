#ifndef FILEMANAGEMENT_EXCEPTION_H
#define FILEMANAGEMENT_EXCEPTION_H

#include <stdexcept>

class FileDoesNotExist : public std::runtime_error {
public:
	FileDoesNotExist() : std::runtime_error("File Does not exist") {}
};
#endif // !FILEMANAGEMENT_EXCEPTION_H
