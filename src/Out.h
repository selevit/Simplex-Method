#ifndef _OUT_H_
#define _OUT_H_

#include <ostream>

class Out
{
public:
	bool use_cp866;
	bool can_output;
	Out& operator<<(int);
	Out& operator<<(const char*);
	Out& operator<<(std::ostream&); 
Out() : use_cp866(false), can_output(true) {};
private:
	std::ostream* p;
	const char* uni_to_cp866(const char*);
};

extern Out _out;

#endif
