///////////////////////////////////////////////////////////////////

// Executive.cpp - Receives all user input and passes it off to 

//				   the Wowrkflow class for processing.

//

// Language: Visual C++

// Platform: MacBook Pro (Windows 10 Virtual Machine)

// Application: Project 1, Single Node Map/Reduce Program

// Author: Rob Hardisty

// Syracuse University, CSE 687 - Object Oriented Design

// rlhardis@syr.edu

//

///////////////////////////////////////////////////////////////////



/*#include <iostream>

#include <limits>

#include "workflow.h"

#include "file_management.h"



bool isValid(std::string);*/





/*

 METHOD/OPERATION:	main(int, char*)

	  DESCRIPTION:	Main program

		   INPUTS:	Integer argument count, argument list

		  RETURNS:	Integer exit code

*/

/*int main()

{

	try

	{

		// Debugging to determine execution time of the MapReduce processes

#ifdef _DEBUG

		auto start = clock();

#endif // DEBUG



		// Jump out if the number of arguments are incorrect 

		// (should be 4, default exe, input, temp, output directories)

		/*if (argc != 4)

			return 0;



		// Check to see if the folders exist

		if (!isValid(argv[1]))

			return 0;

		if (!isValid(argv[2]))

			return 0;

		if (!isValid(argv[3]))

			return 0;



		// Kick off the workflow for data processing
		std::string A{ "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\i\\" };
		std::string B{"C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\t\\" };
		std::string C{ "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\o\\" };
		std::string D{ "C:\\Users\\conte\\Documents\\MyDll\\MapReduce.dll" };
		//std::string A{ "C:\\testInput\\" };
		//std::string B{ "C:\\testTemp\\" };
		//std::string C{ "C:\\testOutput\\" };

		Workflow wf;
		int i = wf.WorkflowMain(A, B, C, D);



		// Debugging to determine execution time of the MapReduce processes

#ifdef _DEBUG

		auto stop = clock();

		std::cout.precision(3);

		std::cout << "time (sec): " << std::fixed << (stop - start) / double(CLOCKS_PER_SEC) << std::endl;

#endif // DEBUG

	}

	catch (const std::exception& ex)

	{

		std::cerr << "Main::main::Exception: " << ex.what() << std::endl;

	}

}*/







/*

 METHOD/OPERATION:	isValid(string)

	  DESCRIPTION:	Test to see if the passed in string folders exist

		   INPUTS:	string

		  RETURNS:	boolean

*/

/*bool isValid(std::string userInput)

{

	try

	{

		// Verify the inputted folders exist

		fs::path userPath{ userInput };



		if (fs::is_directory(userPath))

			return true;

		else

			return false;

	}

	catch (const std::exception& ex)

	{

		std::cerr << "Main::isValid::Exception: " << ex.what() << std::endl;

		return false;

	}

}*/



//-------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////

// executive.cpp - Receives all user input and passes it off to 

//				   the Wowrkflow class for processing.

//

// Language: Visual C++

// Platform: MacBook Pro (Windows 10 Virtual Machine)

// Application: Project 1, Single Node Map/Reduce Program

// Author: Rob Hardisty

// Syracuse University, CSE 687 - Object Oriented Design

// rlhardis@syr.edu

//

///////////////////////////////////////////////////////////////////

#include <iostream>

#include "workflow.h"

#include <boost/log/trivial.hpp>



int main(int argc, char* argv[]) {

	BOOST_LOG_TRIVIAL(info) << "Starting application...";

	std::string dir_input;

	std::string dir_temp;

	std::string dir_output;

	std::string dir_dll;

	// Assume empty argument list and use defaults

	if (argc == 1) {

		dir_input = "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\i\\";

		dir_temp = "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\t\\";

		dir_output = "C:\\Users\\conte\\Documents\\GitHub\\CDSE687_OOD\\MapReduce\\MapReduce\\o\\";

		dir_dll = "C:\\Users\\conte\\Documents\\MyDLL\\MapReduce.dll";

	}else if (argc == 5) {

		dir_input = argv[1];

		dir_temp = argv[2];

		dir_output = argv[3];

		dir_dll = argv[4];

	}
	else {

		BOOST_LOG_TRIVIAL(error) << "ERROR evaluating argument list::USAGE: <input_dir> <temp_dir> <output_dir> <dll_dir>";

		return -1;

	}

	BOOST_LOG_TRIVIAL(info) << "Entering workflow...";

	Workflow wf;

	wf.WorkflowMain(dir_input, dir_temp, dir_output, dir_dll);

	return 0;

}