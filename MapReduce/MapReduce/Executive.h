#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <boost/log/trivial.hpp>

#include <iostream>
using std::string;

class Executive
{
public:
	Executive();
	~Executive();

	string getUserInput();
	void setInputPath(string);
	void setOutputPath(string);
	void setTempPath(string);

private:

};


#endif // !1