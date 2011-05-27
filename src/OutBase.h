#ifndef _OUTBASE_H_
#define _OUTBASE_H_

#include <ostream>

class OutBase
{
public:
	bool can_output;
	bool stdin_isatty;
	OutBase& operator<<(int);
	virtual OutBase& operator<<(const char*) = 0;
	OutBase& operator<<(std::ostream&); 
OutBase() : can_output(true) {};
protected:
	std::ostream* p;
};

#endif
