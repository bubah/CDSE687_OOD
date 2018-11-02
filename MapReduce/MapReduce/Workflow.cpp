///////////////////////////////////////////////////////////////////
// Workflow.cpp - Ties together all of the MapReduce processes
//
// Language: Visual C++
// Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 1, Single Node Map/Reduce Program
// Author: Rob Hardisty
// Syracuse University, CSE 687 - Object Oriented Design
// rlhardis@syr.edu
//
///////////////////////////////////////////////////////////////////

#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Sort.h"
#include "Reduce.h"


// Constructor taking all of the user udentified working directories
Workflow::Workflow(string inputDir, string outputDir, string tempDir )
	:dirInput{ inputDir }, dirTemp{ tempDir }, dirOutput{ outputDir }
{
	BOOST_LOG_TRIVIAL(info) << "Instantiating the Workflow object using class constructor" << "\n";
	// Declare an instance of the FileManagement class
	FileManagement fm(dirInput, dirTemp, dirOutput);

	////////////////////////////////////////////////////////////////////
	///////////////////////////////|   MAP
	////////////////////////////////////////////////////////////////////
	// Run the map process
	Map mp;
	while ("-1" != fm.getInputFileName())
	{
		mp.mapper(fm.getInputFileName(), fm.readFromInputFile(fm.getInputFileName()), fm.getTmpFileName(), fm);

		// Increment the iterator for the file pointer
		fm.incrementInputFilePointer();
	}

	//export map data to temp file
	mp.exportt(fm.getTmpFileName(), fm);

	// Load in and pass in the temp string to the reducer
	string mapData = fm.readFromTmpFile(fm.getTmpFileName());


	////////////////////////////////////////////////////////////////////
	///////////////////////////////|   REDUCE
	////////////////////////////////////////////////////////////////////
	// Run the reduce process and write SUCCESS file when complete
	Reduce rd(dirOutput);

	// Reduce the sorted map data
	vector< std::pair<string, int> > vectorData = rd.Reducer(mapData, fm);

	// Sort the reduced map data prior to writing to output directory
	Sort st;
	st.sortVectorData(vectorData);

	// Write the reduced/sorted map data
	fm.writeToOutputFile(fm.getOutputFileName(), vectorData);

	// Write the SUCCESS file
	rd.writeSuccessFile(fm);
}