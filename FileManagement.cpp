#include "FileManagement.h"
#include "FileManagementException.h"

FileManagement::FileManagement() :inputDir{ "" }, tmpDir{ "" }, outputDir{ "" } {}


FileManagement::FileManagement(string inputD, string tmpD, string outputD) :inputDir{inputD}, tmpDir{tmpD}, outputDir{outputD}
{}


void FileManagement::writeToInputFile(string inputFileName, string fileContent) 
{
	fs::path inputFile_Path(inputFileName);

	try {
		if (!exists(inputFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
			
		}
		else //else print content to file
		{
			fs::ofstream ofs{ inputFileName, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << inputFileName << " error: " << error1.what() << std::endl;
	}
}


string FileManagement::readFromInputFile(string inputFileName)
{
	fs::path inputFile_Path(inputFileName);
	string record{""}; // Declare string variable for storing file content

	try {
		if (!exists(inputFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
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
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << inputFileName << " error: " << error1.what() << std::endl;
	}
	
	return record;
}


void FileManagement::writeToTmpFile(string tmpFileName, string fileContent)
{
	fs::path tmpFile_Path(tmpFileName);

	try {
		if (!exists(tmpFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			fs::ofstream ofs{ tmpFileName, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << tmpFileName << " error: " << error1.what() << std::endl;
	}
}


void FileManagement::writeToTmpFile(string tmpFileName, vector<string> fileContent)
{
	fs::path tmpFile_Path(tmpFileName);

	try {
		if (!exists(tmpFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{	
			fs::ofstream ofs{ tmpFileName, std::ios_base::trunc }; // Clears content in file
			ofs.close(); // Close file

			for (string &w : fileContent) {
				ofs.open( tmpFileName, std::ios_base::app );
				ofs << w << '\n';
				ofs.close();
			}
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << tmpFileName << " error: " << error1.what() << std::endl;
	}
}


string FileManagement::readFromTmpFile(string tmpFileName)
{
	fs::path tmpFile_Path(tmpFileName);
	string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(tmpFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else read content from file line
		{
			string tempString{ "" };
			fs::ifstream ifs{ tmpFile_Path };
			while (getline(ifs, tempString)) {
				record += (tempString + " ");
			}

		}
	}
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << tmpFileName << " error: " << error1.what() << std::endl;
	}

	return record;
}


void FileManagement::writeToOutputFile(string outputFileName, string fileContent)
{
	fs::path outputFile_Path(outputFileName);

	try {
		if (!exists(outputFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			fs::ofstream ofs{ outputFileName, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << outputFileName << " error: " << error1.what() << std::endl;
	}
}


void FileManagement::writeToOutputFile(string outputFileName, vector<string> fileContent)
{
	fs::path outputFile_Path(outputFileName);

	try {
		if (!exists(outputFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			for (string &w : fileContent) {
				fs::ofstream ofs{ outputFileName, std::ios_base::app };
				ofs << w << '\n';
				ofs.close();
			}
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << outputFileName << " error: " << error1.what() << std::endl;
	}
}


string FileManagement::readFromOutputFile(string outputFileName)
{
	fs::path outputFile_Path(outputFileName);
	string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(outputFile_Path)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
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
	catch (FileDoesNotExist &error1) //
	{
		std::cerr << "File " << outputFileName << " error: " << error1.what() << std::endl;
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
		return "-1";
	}
	fs::path inputFileName_Path{ *inputDirItr };
	return inputFileName_Path.string();
}


string FileManagement::getTmpFileName()
{
	if (tmpDirItr == fs::directory_iterator{}) {
		return "-1";
	}
	fs::path tmpFileName_Path{ *tmpDirItr };
	return tmpFileName_Path.string();
}


string FileManagement::getOutputFileName()
{
	if (outputDirItr == fs::directory_iterator{}) {
		return "-1";
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