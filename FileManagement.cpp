#include "FileManagement.h"

FileManagement::FileManagement() :inputDir{ "" }, tmpDir{ "" }, outputDir{ "" } {}

FileManagement::FileManagement(string inputD, string tmpD, string outputD) :inputDir{inputD}, tmpDir{tmpD}, outputDir{outputD}
{}

void FileManagement::writeToInputFile(string inputFileName, string fileContent) 
{
	fs::path inputFile_Path(inputFileName);

	try {
		if (!exists(inputFile_Path)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else print content to file
		{
			fs::ofstream ofs{ inputFileName, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		cout << "write to input error" << endl;
		abort(); 
	}
}

string FileManagement::readFromInputFile(string inputFileName)
{
	fs::path inputFile_Path(inputFileName);
	string record{""}; // Declare string variable for storing file content

	try {
		if (!exists(inputFile_Path)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else read content from file line
		{
			string tempString;
			fs::ifstream ifs{ inputFile_Path };
			while (getline(ifs, tempString)) {
				record += (tempString + " ");
			}

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

void FileManagement::writeToTmpFile(string tmpFileName, string fileContent)
{
	fs::path tmpFile_Path(tmpFileName);

	try {
		if (!exists(tmpFile_Path)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else print content to file
		{
			fs::ofstream ofs{ tmpFileName, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		cout << "write to tmp file error" << endl;
		abort();
	}
}

string FileManagement::readFromTmpFile(string tmpFileName)
{
	fs::path tmpFile_Path(tmpFileName);
	string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(tmpFile_Path)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else read content from file line
		{
			string tempString;
			fs::ifstream ifs{ tmpFile_Path };
			while (getline(ifs, tempString)) {
				record += (tempString + " ");
			}

		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		cout << "Read from tmp file error" << endl;
		abort();
	}

	return record;
}

void FileManagement::writeToOutputFile(string outputFileName, string fileContent)
{
	fs::path outputFile_Path(outputFileName);

	try {
		if (!exists(outputFile_Path)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else print content to file
		{
			fs::ofstream ofs{ outputFileName, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		cout << "write to ouput error" << endl;
		abort();
	}
}

string FileManagement::readFromOutputFile(string outputFileName)
{
	fs::path outputFile_Path(outputFileName);
	string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(outputFile_Path)) // if file does not exist throw error and abort program/process
		{
			cout << "File does not exist" << endl;
		}
		else //else read content from file line
		{
			string tempString;
			fs::ifstream ifs{ outputFile_Path };
			while (getline(ifs, tempString)) {
				record += (tempString + " ");
			}

		}
	}
	catch (fs::filesystem_error &error1) //
	{
		std::cerr << error1.what() << std::endl;
		abort();
	}

	return record;
}

/*void FileManagement::createFile(string fileName)
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
}*/

string FileManagement::getInputFileName()
{
	if (inputDirItr == fs::directory_iterator{}) {
		return "@abort";
	}
	fs::path inputFileName_Path{ *inputDirItr };
	return inputFileName_Path.string();
}

string FileManagement::getTmpFileName()
{
	if (tmpDirItr == fs::directory_iterator{}) {
		cout << "Points to end of directory" << endl;
		abort();
	}
	fs::path tmpFileName_Path{ *tmpDirItr };
	return tmpFileName_Path.string();
}

string FileManagement::getOutputFileName()
{
	if (outputDirItr == fs::directory_iterator{}) {
		cout << "Points to end of directory" << endl;
		abort();
	}
	fs::path outputFileName_Path{ *outputDirItr };
	return outputFileName_Path.string();
}

void FileManagement::incrementInputFilePointer()
{
	inputDirItr++;
}
void FileManagement::incrementTmpFilePointer()
{
	tmpDirItr++;
}

void FileManagement::incrementOutputFilePointer()
{
	outputDirItr++;
}

fs::path FileManagement::getInputDir()
{
	return inputDir;
}