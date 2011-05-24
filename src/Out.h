#ifndef _OUT_H_
#define _OUT_H_

#include <ostream>

class Out
{
public:
	bool can_output;
	bool stdin_is_a_terminal;
	bool stdout_is_a_terminal;
	Out& operator<<(int);
	Out& operator<<(const char*);
	Out& operator<<(std::ostream&); 
	Out();
private:
	std::ostream* p;
	const char* uni_to_cp866(const char*);
};

extern Out _out;

#endif
