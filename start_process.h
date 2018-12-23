#ifndef START_MAP_H
#define START_MAP_H

#pragma once

#include <string>

class StartProcess {
public:
	void StartMap(std::string &arguments);
	void StartReduce(std::string &arguments);
};

#endif // START_MAP_H
