////////////////////////////////////////////////////////////////////////////////
// FileManagement.cpp - Application interface to the filesystem operations		
// ver 1.0																			
// Language:    C++, Visual Studio 2017											
// Platform:    Microsoft Surface Pro 4, Windows 10								
// Application: Project 1, Single Node Map/Reduce Program						
// Author:      Bubah Conteh, 
//				Syracuse University CSE 687 - Object Oriented Design
//              bconteh@syr.edu														
////////////////////////////////////////////////////////////////////////////////


#include "FileManagement.h"
#include "FileManagementException.h"


FileManagement::FileManagement(string inputD, string tmpD, string outputD) 
	: inputDir{ inputD }, tmpDir{ tmpD }, outputDir{ outputD }
{BOOST_LOG_TRIVIAL(info) << "Instantiating a file management object using constructor" << "\n"; }


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
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << inputFileName << "'. "
			<< error1.what() << std::endl;
	}
}


string FileManagement::readFromInputFile(string inputFileName)
{
	BOOST_LOG_TRIVIAL(info) << "Now reading input directory from file '" << inputFileName << "'" << "\n";
	fs::path inputFile_Path(inputFileName);
	string record{ "" }; // Declare string variable for storing file content

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
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << inputFileName << "'. "
			<< error1.what() << std::endl;
	}

	return record;
}


void FileManagement::writeToTmpFile(string tmpFileName, 
									string fileContent)
{
	fs::path tmp(tmpDir);
	
	try {
		if (!exists(tmp)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			tmp.append(tmpFileName);
			fs::ofstream ofs{ tmp, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << tmpFileName << "'. "
			<< error1.what() << std::endl;
	}
}


void FileManagement::writeToTmpFile(string tmpFileName, 
									vector<string> fileContent)
{
	fs::path tmp(tmpDir);

	try {
		if (!exists(tmp)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			tmp.append(tmpFileName);
			fs::ofstream ofs{ tmp, std::ios_base::trunc }; // Clears content in file
			ofs.close(); // Close file

			for (string &w : fileContent) {
				ofs.open(tmp, std::ios_base::app);
				ofs << w << '\n';
				ofs.close();
			}
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << tmpFileName << "'. "
			<< error1.what() << std::endl;
	}
}


string FileManagement::readFromTmpFile(string tmpFileName)
{
	BOOST_LOG_TRIVIAL(info) << "Now reading interm directory from file '" << tmpFileName << "'" << "\n";
	fs::path tmp(tmpDir);
	string record{ "" }; // Declare string variable for storing file content

	try {
		if (!exists(tmp)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else read content from file line
		{
			string tempString{ "" };
			fs::ifstream ifs{ tmp.append(tmpFileName) };
			while (getline(ifs, tempString)) {
				record += (tempString + " ");
			}

		}
	}
	catch (FileDoesNotExist &error1) //
	{
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << tmpFileName << "'. "
			<< error1.what() << std::endl;
	}

	return record;
}


void FileManagement::writeToOutputFile(string outputFileName, string fileContent)
{
	BOOST_LOG_TRIVIAL(info) << "Now writing to output directory to file '" << outputFileName << "'" << "\n";
	// Make a copy to avoid overwriting the private data member
	fs::path tmp = outputDir;

	try {
		if (!exists(tmp)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			tmp.append(outputFileName);
			fs::ofstream ofs{ tmp, std::ios_base::app };
			ofs << fileContent << '\n';
			ofs.close();
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << outputFileName << "'. "
			<< error1.what() << std::endl;
	}
}


void FileManagement::writeToOutputFile(string outputFileName, 
									vector< std::pair<string, int> > fileContent)
{
	BOOST_LOG_TRIVIAL(info) << "Now writing to output directory to file '" << outputFileName << "'" << "\n";
	fs::path tmp = outputDir;

	try {
		if (!exists(tmp)) // if file does not exist throw error and abort program/process
		{
			throw FileDoesNotExist();
		}
		else //else print content to file
		{
			tmp.append(outputFileName);
			for (auto &w : fileContent) {
				fs::ofstream ofs{ tmp, std::ios_base::app };
				ofs << w.first << ": " << w.second << '\n';
				ofs.close();
			}
		}
	}
	catch (FileDoesNotExist &error1) //
	{
		BOOST_LOG_TRIVIAL(error) << "error writing to file '" << outputFileName << "'. "
			<< error1.what() << std::endl;
	}
}


string FileManagement::readFromOutputFile(string outputFileName)
{
	BOOST_LOG_TRIVIAL(info) << "Now reading output directory from file '" << outputFileName << "'" << "\n";
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
		BOOST_LOG_TRIVIAL(error) << "error reading from file '" << outputFileName << "'. "
			<< error1.what() << std::endl;
	}

	return record;
}


string FileManagement::getInputFileName()
{
	if (inputDirItr == fs::directory_iterator{}) {
		return "-1";
	}
	fs::path inputFileName_Path{ *inputDirItr };

	// If this is a hidden file, ignore it and increment the file pointer
	if (isHidden(inputFileName_Path.filename().string()))
	{
		incrementInputFilePointer();
		if (inputDirItr == fs::directory_iterator{})
			return "-1";

		fs::path inputFileName_Path{ *inputDirItr };
	}

	return inputFileName_Path.string();
}


string FileManagement::getTmpFileName()
{
	if (tmpDirItr == fs::directory_iterator{}) {
		return "temp";
	}
	fs::path tmpFileName_Path{ *tmpDirItr };

	// If this is a hidden file, ignore it and increment the file pointer
	if (isHidden(tmpFileName_Path.filename().string()))
	{
		incrementTmpFilePointer();
		if (tmpDirItr == fs::directory_iterator{})
			return "temp";

		fs::path tmpFileName_Path{ *tmpDirItr };
	}
	return tmpFileName_Path.string();
}


string FileManagement::getOutputFileName()
{
	if (outputDirItr == fs::directory_iterator{}) {
		return "output";
	}
	fs::path outputFileName_Path{ *outputDirItr };

	// If this is a hidden file, ignore it and increment the file pointer
	if (isHidden(outputFileName_Path.filename().string()))
	{
		incrementOutputFilePointer();
		if (outputDirItr == fs::directory_iterator{})
			return "output";

		fs::path outputFileName_Path{ *outputDirItr };
	}

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

fs::path FileManagement::getTempDir()
{
	return tmpDir;
}


bool FileManagement::isHidden(string filename)
{
	return (filename[0] == '.');
}

