#include <ostream>
#include <cstdio>

#ifdef _WIN32
# include <io.h> 
# include <windows.h>
#else
# include <unistd.h>
#endif

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
		if (stdout_isatty)
			s = utf8_to_cp866(s);
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

#ifdef _WIN32
const char* Out::utf8_to_cp866(const char* u)
{
	unsigned int required_size;
	static char *buf = 0;
	wchar_t *wbuf;

	if (buf) // bleh!
		delete[] buf;

	required_size = MultiByteToWideChar(65001, 0, u, -1, 0, 0);
	wbuf = new wchar_t[required_size];
	MultiByteToWideChar(65001, 0, u, -1, wbuf, required_size);

	required_size = WideCharToMultiByte(866, 0, wbuf, -1, 0, 0, 0, 0);
	buf = new char[required_size];
	WideCharToMultiByte(866, 0, wbuf, -1, buf, required_size, 0, 0);
	delete[] wbuf;

	return buf;
}
#endif

Out::Out() : can_output(true)
{
#ifdef _WIN32
	stdin_isatty = _isatty(_fileno(stdin));
	stdout_isatty = _isatty(_fileno(stdout));
#else
	stdin_isatty = isatty(fileno(stdin));
	stdout_isatty = isatty(fileno(stdout));
#endif
}

Out _out;
