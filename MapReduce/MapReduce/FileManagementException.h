#include <stdexcept>

class FileDoesNotExist : public std::runtime_error
{
public:
	FileDoesNotExist()
		: std::runtime_error("File Does not exist") {}
};