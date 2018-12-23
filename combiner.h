///////////////////////////////////////////////////////////////////////////////
//        File: combiner.h
// Description: Combines the intermediate data, prepping for the reduce process
//    Language: Visual C++
//    Platform: MacBook Pro (Windows 10 Virtual Machine)
// Application: Project 3, Single Node Map/Reduce Program
//      Author: Rob Hardisty, rlhardis@syr.edu
//              Syracuse University, CSE 687 - Object Oriented Design
///////////////////////////////////////////////////////////////////////////////
#ifndef COMBINER_H
#define COMBINER_H

#include <boost/tokenizer.hpp>

#include <map>
#include <string>
#include <sstream>

typedef std::map<std::string, std::string> MapStrStr;

class Combiner {
public:
	static MapStrStr Combine(const std::string &kMapData);
};
// Combiner takes in string input from the temp files and combines all key/value
// pairs into a std::map
MapStrStr Combiner::Combine(const std::string &tmp_data) {
    MapStrStr mp;
    std::string key, val;
    std::istringstream iss(tmp_data);
    while (std::getline(std::getline(iss, key, ',') >> std::ws, val))
        if (mp.find(key) == mp.end()) {mp[key] = val;}
        else {mp[key] = mp[key] + "," + val;}
    return mp;
}
#endif
