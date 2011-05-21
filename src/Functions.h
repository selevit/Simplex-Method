#ifndef _ERROR_H_
#define _ERROR_H_

#ifndef _WIN32
#define _(x) x
#endif

class Functions
{
public:
	void die(char* msg, int exit_code);
#ifdef _WIN32
	bool use_cp886;
	char * _(char*);
Functions() : use_cp866(true) {};
#endif

};

#endif
