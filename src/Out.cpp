#include <ostream>
#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
#ifdef _WIN32
		if (stdout_is_a_terminal)
			s = uni_to_cp866(s);
#endif /* _WIN32 */
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

Out::Out() : can_output(true)
{
	struct stat st;
	fstat(stdin->_fileno, &st);
	stdin_is_a_terminal = S_ISCHR(st.st_mode);
	fstat(stdout->_fileno, &st);
	stdout_is_a_terminal = S_ISCHR(st.st_mode);
}

Out _out;
