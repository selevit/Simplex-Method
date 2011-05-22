#ifndef _OUT_H_
#define _OUT_H_

#include <iostream>
#define _(x) x
#define die(s, i) std::cout << s << i;

class Out
{
public:
	bool use_cp866;
	bool can_output;
	Out& operator<<(double);
	Out& operator<<(const char*);
	Out();
private:
	const char* uni_to_cp866(const char*);
	std::map<const char*, const char*> conv_table;
};

extern Out out;

#endif
