#include "FileManagement.h"

FileManagement::FileManagement() :inputDir{ "" }, tmpDir{ "" }, outputDir{ "" } {}

FileManagement::FileManagement(string inputDir, string tmpDir, string outputDir) 
{
	this->inputDir = inputDir;
	this->tmpDir = tmpDir;
	this->outputDir = outputDir;
}

void FileManagement::writeToInputFile(string inputFile, string content) 
{
	fs::path inputFilePath(inputFile);

	try {
		if (!exists(inputFilePath)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else print content to file
		{
			fs::ofstream ofs{ inputFilePath };
			ofs << content << '\n';
		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		abort(); 
	}
}

string FileManagement::readFromInputFile(string inputFile)
{
	fs::path inputFilePath(inputFile);
	string record{""}; // Declare string variable for storing file content

	try {
		if (!exists(inputFilePath)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else read content from file line
		{
			string tempString;
			fs::ifstream ifs{ inputFilePath };
			getline(ifs, tempString);
			record += (tempString + " ");

		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		cout << "Closing process due to file error";
		abort();
	}
	
	return record;
}

void FileManagement::writeToTmpFile(string tmpFile, string content)
{
	fs::path tmpFilePath(tmpFile);

	try {
		if (!exists(tmpFilePath)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else print content to file
		{
			fs::ofstream ofs{ tmpFilePath };
			ofs << content << '\n';
		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		abort();
	}
}

string FileManagement::readFromTmpFile(string tmpFile)
{
	fs::path tmpFilePath(tmpFile);
	string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(tmpFilePath)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else read content from file line
		{
			string tempString;
			fs::ifstream ifs{ tmpFilePath };
			getline(ifs, tempString);
			record += (tempString + " ");

		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		abort();
	}

	return record;
}

void FileManagement::writeToOutputFile(string outputFile, string content)
{
	fs::path outputFilePath(outputFile);

	try {
		if (!exists(outputFilePath)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else print content to file
		{
			fs::ofstream ofs{ outputFilePath };
			ofs << content << '\n';
		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		abort();
	}
}

string FileManagement::readFromOutputFile(string outputFile)
{
	fs::path outputFilePath(outputFile);
	string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(outputFilePath)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else read content from file line
		{
			string tempString;
			fs::ifstream ifs{ outputFilePath };
			getline(ifs, tempString);
			record += (tempString + " ");

		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		abort();
	}

	return record;
}

void FileManagement::createFile(string fileName)
{
	fs::path p1(fileName); //create a path object
	fs::ofstream ofs(p1); //creates file

	try {
		if (ofs.fail())  //if file creation fails print error and abort()
		{
			cout << "File creation fialed!";
		}
		else //Close file
		{
			ofs.close(); 
		}
	}
	catch (fs::filesystem_error &e) {
		std::cerr << e.what() << std::endl;
		abort();
	}
}

fs::directory_iterator FileManagement::getInputFileName()
{
	if (inputDirItr == fs::directory_iterator{}) {
		cout << "Points to end of directory" << endl;
		abort();
	}
	
	return inputDirItr;
}

fs::directory_iterator FileManagement::getTmpFileName()
{
	return tmpDirItr;
}

fs::directory_iterator FileManagement::getOutputFileName()
{
	return outputDirItr;
}