#include <cstdio>
#include <unistd.h>

#include "OutLinux.h"

Out& Out::operator<<(const char* s)
{
	if (can_output)
		*p << s;

	return *this;
}

Out::Out()
{
	stdin_isatty = isatty(fileno(stdin));
}

Out _out;
