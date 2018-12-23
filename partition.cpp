///////////////////////////////////////////////////////////////////////////////
//        File: partition.cpp
// Description: Defines the number of partitions for the Map class and 
//              associated functionality
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Rob Hardisty, rlhardis@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#define NUM_CHARS 26.0
#define ASCII_A   97

#include <math.h>

#include "partition.h"

Partition::Partition() :num_partitions_{ 0 } {}

Partition::Partition(const int &parts)
	:num_partitions_{ parts } {
}

int Partition::GetPartition(const std::string &key) const {
	// Partion value is Zero or less return default partition
	if (num_partitions_ <= 0) {
		return 1;
	}

	return
		((int(key[0]) - ASCII_A) / ceil(NUM_CHARS / num_partitions_)) + 1;
}

std::vector<int> Partition::PartitionMapWorkers(int num_map_processes,
	int num_stubs) {
	// iterates throgh list of file names and partitions them to vector
	int count_map = 0;
	std::vector<int> partitioned_workers(num_stubs);
	for (int index = 0; index < num_stubs; index++) {
		for (int partiton = 0;
			partiton < round((double)num_map_processes / num_stubs);
			partiton++) {
			// if all files have been partitoned, break
			if (count_map >= num_map_processes) {
				break;
			}
			// else concatenate filename to current partition 
			partitioned_workers[index] ++;
			count_map++; // increment file count
		}

		// If last index in vector add remaining workers
		if (index == num_stubs - 1 && count_map < num_map_processes) {
			while (count_map < num_map_processes) { // loop until all files are acounted for
				partitioned_workers[index]++;
				count_map++; // increment file count
			}
		}
	}
	return partitioned_workers; // returned partioned string vector
}

str_vec Partition::PartFileName(const str_vec
	filename_vec, int parts) {
	// temp vector holds partitioned filenames
	str_vec input_file_part;

	int num_file_names = filename_vec.size();

	// if num_map_proc is zero or less return empty vector_str
	if (parts <= 0) {
		return input_file_part;
	}

	for (int proc_index = 0; proc_index < parts; proc_index++) {
		input_file_part.push_back("");
	}

	// iterates throgh list of file names and partitions them to vector
	int count_file = 0;

	for (int index = 0; index < parts; index++) {
		for (int partiton = 0;
			partiton < round((double)num_file_names / parts);
			partiton++) {
			// if all files have been partitoned, break
			if (count_file >= num_file_names) {
				break;
			}
			// else concatenate filename to current partition 
			input_file_part[index] +=
				filename_vec[count_file] + " ";

			count_file++; // increment file count
		}

		// if we have reached last partition and all files not read. add to last part
		if (index == parts - 1 && count_file < num_file_names) {
			while (count_file < parts) { // loop until all files are acounted for
				input_file_part[index] += filename_vec[count_file] + " ";
				count_file++; // increment file count
			}
		}
	}
	return input_file_part; // returned partioned string vector
}

// Partitons file numbers (1, 2, 3 etc) to vector. 
// These numbers are passed to ea. reduce worker as comand line arguments
// when a stub starts a reduce process. Example: 34589_temp_1
// Function will assign 1 to a reduce letting it know its responsible for 
// reading all the ..._temp_1 files.
void Partition::TempFileId(std::vector<int> &ids, std::vector<int>
	&part_reduce_workers) {
	ids[0] = 0; // initialize first index to zero
	int counter = 0; // counter varaible

	for (int index = 1; index < part_reduce_workers.size(); index++) {
		ids[index] = counter;
		for (int index_b = 0; index_b < part_reduce_workers[index - 1];
			index_b++) {
			ids[index]++;
			counter++;
		}
	}
}