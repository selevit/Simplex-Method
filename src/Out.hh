#ifndef _OUT_HH_
#define _OUT_HH_

#include <ostream>

class Out
{
public:
	bool can_output;
	bool stdin_isatty;
	Out& operator<<(int);
	Out& operator<<(const char*);
	Out& operator<<(std::ostream&); 
	Out();
private:
	bool stdout_isatty;
	std::ostream* p;
#ifdef _WIN32
	const char* utf8_to_cp866(const char*);
#endif
};

extern Out _out;

#endif
