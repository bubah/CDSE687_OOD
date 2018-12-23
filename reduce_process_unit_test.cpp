///////////////////////////////////////////////////////////////////////////////
//        File: reduce_process_unit_test.cpp
// Description: Test all classes/funcions in the reduce process executable
//    Language: Visual C++
//    Platform: Windows 10 (visual studio 2017 Community)
// Application: Project 3, Multi-Node map reduce
//      Author: Bubah Conteh, BConteh@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#include "pch.h"

#include <Windows.h>

#include "../Map_Phase/partition.h"
#include "../Map_Phase/partition.cpp"
#include "../Map_Phase/directory_management.h"
#include "../Map_Phase/directory_management.cpp"
#include "../Map_Phase/filemanagement.cpp"
#include "../Map_Phase/filemanagement.h"
#include "../Map_Phase/filemanagement_exception.h"
#include "../Map_Phase/generatefilename.h"
#include "../Map_Phase/helper_functions.h"
#include "../Map_Reduce_Controller/file_aggregator.h"
#include "../Map_Reduce_Controller/file_aggregator.cpp"
#include "../Reduce_Process/combiner.h"

typedef std::vector < std::pair<std::string, std::string>> vec_pair_str_str;
typedef std::pair<std::string, std::string> pair_str_str;
typedef std::map<std::string, std::string> MapStrStr;

///////////////////////////////////////////////////////////////////////////////
//						DirectoryManager Unit Test							 //
///////////////////////////////////////////////////////////////////////////////
struct TestDirManager : public testing::Test {

	DirectoryManagement* dir_obj =
		new DirectoryManagement("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
			"C:\\unitTestOutput\\", "C:\\MyDLL\\");

	void setup() {}

	void TearDown() {
		delete dir_obj;
	}
};

/* Test Directory manager contructor and the GetInputDir
GetTempDir and GetOutputDir functions */
TEST_F(TestDirManager, Constr_and_GetDir_Test) {

	//ACT - invoke getter funcs and store to temp variable
	std::string inputDir = dir_obj->GetInputDir().string();
	std::string tempDir = dir_obj->GetTempDir().string();
	std::string outputDir = dir_obj->GetOutputDir().string();
	std::string dllDir = dir_obj->GetDllDir().string();

	//ASSERT
	ASSERT_STREQ(inputDir.c_str(), "C:\\unitTestInput\\");
	ASSERT_STREQ(tempDir.c_str(), "C:\\unitTestTemp\\");
	ASSERT_STREQ(outputDir.c_str(), "C:\\unitTestOutput\\");
	ASSERT_STREQ(dllDir.c_str(), "C:\\MyDLL\\");
}

/* Test DirectoryMangment copy and asignment constructor */
TEST_F(TestDirManager, CopyConstructor_N_Copy_Assignment) {


	//ACT - Testing copy constr
	DirectoryManagement dir_obj_copy(*dir_obj); //Copy Constr Call
	// Get directory paths
	std::string inputDir = dir_obj_copy.GetInputDir().string();
	std::string tempDir = dir_obj_copy.GetTempDir().string();
	std::string outputDir = dir_obj_copy.GetOutputDir().string();
	std::string dllDir = dir_obj_copy.GetDllDir().string();

	//ASSERT
	ASSERT_STREQ(inputDir.c_str(), "C:\\unitTestInput\\");
	ASSERT_STREQ(tempDir.c_str(), "C:\\unitTestTemp\\");
	ASSERT_STREQ(outputDir.c_str(), "C:\\unitTestOutput\\");
	ASSERT_STREQ(dllDir.c_str(), "C:\\MyDLL\\");

	//ACT - Testing Assignment operator
	DirectoryManagement dir_oby_copyAsgn = *dir_obj;

	std::string inputDir2 = dir_oby_copyAsgn.GetInputDir().string();
	std::string tempDir2 = dir_oby_copyAsgn.GetTempDir().string();
	std::string outputDir2 = dir_oby_copyAsgn.GetOutputDir().string();
	std::string dllDir2 = dir_oby_copyAsgn.GetDllDir().string();

	//ASSERT 
	ASSERT_STREQ(inputDir2.c_str(), "C:\\unitTestInput\\");
	ASSERT_STREQ(tempDir2.c_str(), "C:\\unitTestTemp\\");
	ASSERT_STREQ(outputDir2.c_str(), "C:\\unitTestOutput\\");
	ASSERT_STREQ(dllDir2.c_str(), "C:\\MyDLL\\");
}

/* Test DirectoryManagement GetFileName functions */
TEST(DirManager, GetFileName_Test) {
	//ARRANGE
	boost::filesystem::ofstream{ "C:\\unitTestInput\\input.txt" }; // create file in input dir
	boost::filesystem::ofstream{ "C:\\unitTestTemp\\temp.txt" }; // create file in temp dir

	DirectoryManagement dir_obj2("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
		"C:\\unitTestOutput\\", "C:\\MyDLL\\");

	//ACT
	std::string inputFileName = dir_obj2.GetInputFilename();
	std::string tempFileName = dir_obj2.GetTempFilename();

	// Delete files in input and temp directories
	boost::filesystem::remove("C:\\unitTestInput\\input.txt");
	boost::filesystem::remove("C:\\unitTestTemp\\temp.txt");

	//ASSERT
	ASSERT_STREQ(inputFileName.c_str(), "C:\\unitTestInput\\input.txt");
	ASSERT_STREQ(tempFileName.c_str(), "temp");
}

/* Test DirectoryManagement Iterator functions */
TEST(DirManager, DirectoryManagerIterator_Test) {
	// create test files in input and temp directories
	for (int fileIndex = 0; fileIndex < 3; fileIndex++) {
		boost::filesystem::ofstream{ "C:\\unitTestInput\\input" +
			std::to_string(fileIndex) + ".txt" };

		boost::filesystem::ofstream{ "C:\\unitTestTemp\\temp" +
			std::to_string(fileIndex) + ".txt" };
	}

	DirectoryManagement dir_obj2("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
		"C:\\unitTestOutput\\", "C:\\MyDLL\\");

	// Get file names and Assert
	std::string inputFileName = dir_obj2.GetInputFilename();
	std::string tempFileName = dir_obj2.GetTempFilename();
	ASSERT_STREQ(inputFileName.c_str(), "C:\\unitTestInput\\input0.txt");
	ASSERT_STREQ(tempFileName.c_str(), "temp");

	// Inccrement to next files
	dir_obj2.IncrementInputFilePointer();
	dir_obj2.IncrementTmpFilePointer();
	// Get file name
	inputFileName = dir_obj2.GetInputFilename();
	tempFileName = dir_obj2.GetTempFilename();
	//ASSERT
	ASSERT_STREQ(inputFileName.c_str(), "C:\\unitTestInput\\input1.txt");
	ASSERT_STREQ(tempFileName.c_str(), "temp");

	// Incremtne a second time
	dir_obj2.IncrementInputFilePointer();
	dir_obj2.IncrementTmpFilePointer();
	// Get file name
	inputFileName = dir_obj2.GetInputFilename();
	tempFileName = dir_obj2.GetTempFilename();
	//ASSERT
	ASSERT_STREQ(inputFileName.c_str(), "C:\\unitTestInput\\input2.txt");
	ASSERT_STREQ(tempFileName.c_str(), "temp");

	// Delete file names
	for (int fileIndex = 0; fileIndex < 3; fileIndex++) {
		boost::filesystem::remove("C:\\unitTestInput\\input" +
			std::to_string(fileIndex) + ".txt");

		boost::filesystem::remove("C:\\unitTestTemp\\temp" +
			std::to_string(fileIndex) + ".txt");
	}
}

TEST(DirManager, DirectoryManagerGetFileNameFromPath_Test) {
	// ARRANGE
	DirectoryManagement dir_obj2("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
		"C:\\unitTestOutput\\", "C:\\MyDLL\\");
	//ACT
	std::string fileName = "C:\\unitTestInput\\input.txt";

	std::string inputFileName = dir_obj2.GetFilenameFromPath(fileName);

	//ASSERT
	ASSERT_STREQ(inputFileName.c_str(), "input.txt");
}

///////////////////////////////////////////////////////////////////////////////
//				End of DirectoryManager Unit Test							 //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//						FileManager Unit Test								 //
///////////////////////////////////////////////////////////////////////////////
struct TestFileManager : public testing::Test {

	FileManagement* file_obj =
		new FileManagement;

	void setup() {
		boost::filesystem::path temp_path{ "C:\\unitTestTemp\\temp1.txt" };
		boost::filesystem::path output_path{ "C:\\unitTestOutput\\output1.txt" };
	}

	void TearDown() {
		boost::filesystem::remove("C:\\unitTestTemp\\temp1.txt");
		boost::filesystem::remove("C:\\unitTestOutput\\output1.txt");
		delete file_obj;
	}
};

/* Test Filemanager read line function */
TEST_F(TestFileManager, TestReadLineFunc) {
	boost::filesystem::path temp_path{ "C:\\unitTestTemp\\temp1.txt" };
	boost::filesystem::ofstream ofs(temp_path, std::ios_base::app);
	ofs << "First Line" << '\n' << "Second Line" << std::endl; // print data to first and second lines
	//ACT
	std::string file_name = "C:\\unitTestTemp\\temp1.txt";
	boost::filesystem::ifstream ifs{ temp_path };
	std::string data = file_obj->ReadLineFromFile(file_name, &ifs); // Read first line

	//ASSERT 
	ASSERT_STREQ(data.c_str(), "First Line ");

	data = file_obj->ReadLineFromFile(file_name, &ifs); // Read Second line
	ASSERT_STREQ(data.c_str(), "Second Line "); //ASSERT
}

/* Test Filemanager read whole file function */
TEST_F(TestFileManager, TestReadWholeFileFunc) {
	boost::filesystem::path temp_path{ "C:\\unitTestTemp\\temp1.txt" };
	boost::filesystem::path temp_dir{ "C:\\unitTestTemp\\" };
	boost::filesystem::ofstream ofs(temp_path, std::ios_base::app);
	ofs << "First Line" << '\n' << "Second Line" << std::endl; // print data to first and second lines 

	//ACT
	std::string file_name = "temp1.txt";
	std::string data = file_obj->ReadWholeFile(file_name, temp_dir); // Read whole file data

	//ASSERT
	ASSERT_STREQ(data.c_str(), "First Line\nSecond Line\n");
}

/* Test Filemanager Write to temp file function */
TEST_F(TestFileManager, Test_WriteToTemp_Func) {
	boost::filesystem::path temp_dir{ "C:\\unitTestTemp\\" };
	vec_pair_str_str key_value;
	pair_str_str A;
	pair_str_str B;

	// Test data to be written to file
	A.first = "Test"; A.second = "1";
	B.first = "Write"; B.second = "2";

	key_value.push_back(A);
	key_value.push_back(B);

	// configured file name to read from when checking data
	DWORD id = GetCurrentProcessId();
	std::string configFilename = std::to_string(id) + "_" + "temp" + "_" + "0";
	std::string file_name = "temp";
	file_obj->WriteToTempFile(file_name, key_value, temp_dir, 3); // write to temp

	// Create path to file
	boost::filesystem::path temp_path{ configFilename };
	temp_dir.append(configFilename);
	std::string tmp_str;

	// Read temp data to verify Write function is working properly
	std::string temp_data;
	boost::filesystem::ifstream ifs{ temp_dir };
	while (getline(ifs, tmp_str)) {
		temp_data += tmp_str + " ";
	}
	ifs.close(); // Close file
	boost::filesystem::remove(temp_dir); // delete file

	//ASSERT
	ASSERT_STREQ(temp_data.c_str(), "Test,1 Write,2 ");
}

/* Test Filemanager Write to output file function */
TEST_F(TestFileManager, Test_WriteToOutput_Func) {
	boost::filesystem::path output_dir{ "C:\\unitTestOutput\\" };
	MapStrStr map_data;
	pair_str_str C, D;
	C.first = "Output"; C.second = "Test";
	D.first = "Second"; D.second = "Line";

	map_data.insert(C);
	map_data.insert(D);
	DWORD id = GetCurrentProcessId();
	std::string configFilename = std::to_string(id) + "_" + "output";
	std::string file_name_out = "output";

	file_obj->WriteToOutputFile(file_name_out, map_data, output_dir); // write to output

	output_dir.append(configFilename);
	boost::filesystem::ifstream ifs2{ output_dir };
	std::string out_str;

	// Read output data
	std::string output_data;
	while (getline(ifs2, out_str)) {
		output_data += out_str + " ";
	}
	ifs2.close();
	boost::filesystem::remove(output_dir); // delete file
	ASSERT_STREQ(output_data.c_str(), "Output: Test Second: Line "); // check output data read
}
///////////////////////////////////////////////////////////////////////////////
//						End of FileManager Unit Test						 //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//						generatefilename Unit Test							 //
///////////////////////////////////////////////////////////////////////////////

/* This generate file name function(s) */
TEST(GenerateFileName, Test1) {
	std::string filename = "Test"; // default file name to be used in file name
	int part = 1; // partition value

	// generate a configured filename (incl. proc id, filename and partition val.
	std::string config_filename = GenerateFileName(filename, part);
	DWORD id = GetCurrentProcessId(); // Get process id

	// check config name against this string
	std::string check_name = std::to_string(id) + "_" + "Test" + "_" + "1";

	//ASSERT
	ASSERT_STREQ(config_filename.c_str(), check_name.c_str());

	// Test overloaded function
	std::string filename2 = "Test2"; // default file name

	// generate a configured file name with proc id and filename and part value
	config_filename = GenerateFileName(filename2);
	id = GetCurrentProcessId(); // Get process id

	// check config name against this string
	check_name = std::to_string(id) + "_" + "Test2";

	//ASSERT
	ASSERT_STREQ(config_filename.c_str(), check_name.c_str());
}

///////////////////////////////////////////////////////////////////////////////
//						End of generatefilename Unit Test					 //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//						Helper functions Unit Test							 //
///////////////////////////////////////////////////////////////////////////////
/* Test EmptyBuffer function when it exceeds capacity */
TEST(TestEmptyBuffer, Test_EmptyBuffer_cap) {
	//ARRANGE
	DirectoryManagement dm_obj("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
		"C:\\unitTestOutput\\", "C:\\MyDLL\\");
	boost::filesystem::path temp_dir{ "C:\\unitTestTemp\\" }; // temp directory
	std::string filename2 = "temp"; // default file name
	DWORD id = GetCurrentProcessId(); // Get process id

	// check config name against this string
	std::string filname_name = std::to_string(id) + "_" + filename2 + "_" + "0";
	temp_dir.append(filname_name); // append to path

	// create memory in heap to store buffered data
	vec_pair_str_str *buffered_memory, myVec, key_value;
	buffered_memory = &myVec; // se vector pointer to myVec

	pair_str_str A, B, C, D; // Declare temp variables to hold data
	A.first = "Test"; A.second = "1";
	B.first = "Write"; B.second = "2";
	C.first = "Output"; C.second = "Test";
	D.first = "Second"; D.second = "Line";
	buffered_memory->push_back(A);
	buffered_memory->push_back(B);
	buffered_memory->push_back(C);
	buffered_memory->push_back(D);

	//ACT
	EmptyBuffer(buffered_memory, 3, dm_obj, 1);

	boost::filesystem::ifstream ifs{ temp_dir };
	std::string temp_str;
	std::string temp_data;
	while (getline(ifs, temp_str)) {
		temp_data += temp_str + " ";
	}
	ifs.close();
	boost::filesystem::remove(temp_dir); // delete file

	ASSERT_STREQ(temp_data.c_str(), "Test,1 Write,2 Output,Test Second,Line "); // check temp data read
	ASSERT_EQ(buffered_memory->size(), 0); // buffer size should be zero
}

/* Test EmptyBuffer function when its below capacity */
TEST(TestEmptyBuffer, Test_EmptyBuffer_doesnt_reach_cap) {
	//ARRANGE
	DirectoryManagement dm_obj("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
		"C:\\unitTestOutput\\", "C:\\MyDLL\\");
	boost::filesystem::path temp_dir{ "C:\\unitTestTemp\\" }; // temp directory
	std::string filename2 = "temp"; // default file name
	DWORD id = GetCurrentProcessId(); // Get process id

	// check config name against this string
	std::string filname_name = std::to_string(id) + "_" + filename2 + "_" + "0";
	temp_dir.append(filname_name); // append to path

	// create memory in heap to store buffered data
	vec_pair_str_str *buffered_memory, myVec, key_value;
	buffered_memory = &myVec; // se vector pointer to myVec

	pair_str_str A, B, C, D; // Declare temp variables to hold data
	A.first = "Test"; A.second = "1";
	B.first = "Write"; B.second = "2";
	C.first = "Output"; C.second = "Test";
	D.first = "Second"; D.second = "Line";
	buffered_memory->push_back(A);
	buffered_memory->push_back(B);
	buffered_memory->push_back(C);
	buffered_memory->push_back(D);

	//ACT
	EmptyBuffer(buffered_memory, 5, dm_obj, 1);

	boost::filesystem::ifstream ifs{ temp_dir };
	std::string temp_str;
	std::string temp_data;
	while (getline(ifs, temp_str)) {
		temp_data += temp_str + " ";
	}
	ifs.close();
	boost::filesystem::remove(temp_dir);

	ASSERT_STREQ(temp_data.c_str(), ""); // No data should be written to file
	ASSERT_EQ(buffered_memory->size(), 4); // buffer size should be same (not zero)
}

/* Test EmptyBuffer function when its equal to capacity */
TEST(TestEmptyBuffer, Test_EmptyBuffer_at_cap) {
	//ARRANGE
	DirectoryManagement dm_obj("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
		"C:\\unitTestOutput\\", "C:\\MyDLL\\");
	boost::filesystem::path temp_dir{ "C:\\unitTestTemp\\" }; // temp directory
	std::string filename2 = "temp"; // default file name
	DWORD id = GetCurrentProcessId(); // Get process id

	// check config name against this string
	std::string filname_name = std::to_string(id) + "_" + filename2 + "_" + "0";
	temp_dir.append(filname_name); // append to path

	// create memory in heap to store buffered data
	vec_pair_str_str *buffered_memory, myVec, key_value;
	buffered_memory = &myVec; // se vector pointer to myVec

	pair_str_str A, B, C, D; // Declare temp variables to hold data
	A.first = "Test"; A.second = "1";
	B.first = "Write"; B.second = "2";
	C.first = "Output"; C.second = "Test";
	D.first = "Second"; D.second = "Line";
	buffered_memory->push_back(A);
	buffered_memory->push_back(B);
	buffered_memory->push_back(C);
	buffered_memory->push_back(D);

	//ACT
	EmptyBuffer(buffered_memory, 4, dm_obj, 1);

	boost::filesystem::ifstream ifs{ temp_dir };
	std::string temp_str;
	std::string temp_data;
	while (getline(ifs, temp_str)) {
		temp_data += temp_str + " ";
	}
	ifs.close();
	boost::filesystem::remove(temp_dir);

	ASSERT_STREQ(temp_data.c_str(), ""); // No data should be written to file
	ASSERT_EQ(buffered_memory->size(), 4); // buffer size should be same (not zero)
}

/* Test Emit function when  */
TEST(TestEmit, Test_helper_func_Emit) {

	// Test Emit when buffer is exceeded
	//ARRANGE
	DirectoryManagement dm_obj("C:\\unitTestInput\\", "C:\\unitTestTemp\\",
		"C:\\unitTestOutput\\", "C:\\MyDLL\\");
	FileManagement fm_obj;

	boost::filesystem::path temp_dir{ "C:\\unitTestTemp\\" }; // temp directory
	std::string filename2 = "temp"; // default file name
	DWORD id = GetCurrentProcessId(); // Get process id
	// check config name against this string
	std::string filname_name = std::to_string(id) + "_" + filename2 + "_" + "0";
	temp_dir.append(filname_name); // append to path

	// create memory in heap to store buffered data
	vec_pair_str_str *buffered_memory, myVec;
	int num_partitions = 1;
	std::vector<std::string> words{ "Unit", "Test", "Emit", "Function" };
	std::vector<std::string> value{ "0", "1", "2", "3" };
	buffered_memory = &myVec;

	//ACT
	for (int index = 0; index < words.size(); index++) {
		Emit(words[index], value[index], dm_obj, 3, buffered_memory, num_partitions);
	}

	std::string temp_str;
	std::string temp_data;
	boost::filesystem::ifstream ifs{ temp_dir };
	while (getline(ifs, temp_str)) {
		temp_data += temp_str + " ";
	}
	ifs.close();
	boost::filesystem::remove(temp_dir);

	ASSERT_STREQ(temp_data.c_str(), "Unit,0 Test,1 Emit,2 Function,3 ");
	ASSERT_EQ(buffered_memory->size(), 0); // buffer size should Zero (cap reached)

	// Test Emit when buffer has not been exceeded.
	for (int index = 0; index < words.size(); index++) {
		Emit(words[index], value[index], dm_obj, 4, buffered_memory, num_partitions);
	}

	std::string temp_str2;
	std::string temp_data2;
	boost::filesystem::ifstream ifs2{ temp_dir };
	while (getline(ifs2, temp_str2)) {
		temp_data2 += temp_str2 + " ";
	}
	ifs2.close();
	boost::filesystem::remove(temp_dir);

	ASSERT_STREQ(temp_data2.c_str(), ""); // No data should write to file cap not exceeded
	ASSERT_EQ(buffered_memory->size(), 4); // buffer size should have a size 4
}

///////////////////////////////////////////////////////////////////////////////
//							End Helper functions Unit Test					 //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//							Partition functions Unit Test					 //
///////////////////////////////////////////////////////////////////////////////
/* Test partion function when  */
TEST(TestPartition, Test_partition) {
	// Test with partiton value of ZERO
	Partition part_obj(0);

	std::vector<std::string> word{ "apple", "mango", "yam" };
	std::vector<int> part(3);
	for (int index = 0; index < word.size(); index++) {
		part[index] = part_obj.GetPartition(word[index]);
	}

	ASSERT_EQ(part[0], 1); // ASSERT
	ASSERT_EQ(part[1], 1);
	ASSERT_EQ(part[2], 1);

	// Test with Negative partition value
	Partition part_obj_2(-1);
	for (int index = 0; index < word.size(); index++) {
		part[index] = part_obj_2.GetPartition(word[index]);
	}

	ASSERT_EQ(part[0], 1); // ASSERT
	ASSERT_EQ(part[1], 1);
	ASSERT_EQ(part[2], 1);

	// Test with a Positive partition value (1)
	Partition part_obj_3(1);
	for (int index = 0; index < word.size(); index++) {
		part[index] = part_obj_3.GetPartition(word[index]);
	}

	ASSERT_EQ(part[0], 1); // ASSERT
	ASSERT_EQ(part[1], 1);
	ASSERT_EQ(part[2], 1);

	// Test with a Positive partition value (3)
	Partition part_obj_4(3);
	for (int index = 0; index < word.size(); index++) {
		part[index] = part_obj_4.GetPartition(word[index]);
	}

	ASSERT_EQ(part[0], 1); // ASSERT
	ASSERT_EQ(part[1], 2);
	ASSERT_EQ(part[2], 3);
}
///////////////////////////////////////////////////////////////////////////////
//	End Partition functions Unit Test	
///////////////////////////////////////////////////////////////////////////////
