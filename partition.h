///////////////////////////////////////////////////////////////////////////////
//        File: partition.h
// Description: Defines the number of partitions for the Map class and 
//              associated functionality
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Rob Hardisty, rlhardis@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////

#ifndef PARTITION_H
#define PARTITION_H

#include <iostream>
#include <vector>

typedef std::vector<int> int_vec;
typedef std::vector<std::string> str_vec;

class Partition {
public:

	Partition();
	Partition(const int &numparts);
	int GetPartition(const std::string &key) const;
	int_vec
	PartitionMapWorkers(int num_map_proc, int num_stubs);
	str_vec 
	PartFileName(const str_vec filename_vec, int parts);

	void TempFileId(std::vector<int> &ids, std::vector<int>
		&part_reduce_workers);

private:
	const int num_partitions_;
};

#endif // PARTITION_H
