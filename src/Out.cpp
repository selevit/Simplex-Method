#include <ostream>

#include "Out.h"

Out& Out::operator<<(int d)
{
	if (can_output)
		*p << d;

	return *this;
}

Out& Out::operator<<(const char* s)
{
	if (can_output) {
		if (use_cp866)
			s = uni_to_cp866(s);
		*p << s;
	}

	return *this;
}

Out& Out::operator<<(std::ostream& s)
{
	p = &s;

	return *this;
}

const char* Out::uni_to_cp866(const char* s)
{
	return s;
}

Out _out;
