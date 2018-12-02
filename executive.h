#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <boost/log/trivial.hpp>
#include <iostream>

class Executive
{
public:
	Executive();
	~Executive();

	const std::string getUserInput();
	void setInputPath(const std::string&);
	void setOutputPath(const std::string&);
	void setTempPath(const std::string&);

private:

};

#endif // 1
