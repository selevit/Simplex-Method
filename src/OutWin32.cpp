#include <cstdio>

#include <windows.h>
#include <io.h>

#include "OutWin32.h"

Out& Out::operator<<(const char* s)
{
	if (can_output) {
		if (stdout_isatty)
			s = utf8_to_cp866(s);
		*p << s;
	}

	return *this;
}

const char* Out::utf8_to_cp866(const char* u)
{
	unsigned int required_size;
	static char *buf = 0;
	wchar_t *wbuf;

	if (buf) // bleh!
		delete[] buf;

	required_size = MultiByteToWideChar(65001, 0, u, -1, 0, 0);
	wbuf = new wchar_t[required_size];
	MultiByteToWideChar(65001, 0, u, -1, wbuf, 100);

	required_size = WideCharToMultiByte(866, 0, wbuf, -1, 0, 0, 0, 0);
	buf = new char[required_size];
	WideCharToMultiByte(866, 0, wbuf, -1, buf, 100, 0, 0);
	delete[] wbuf;

	return buf;
}

Out::Out()
{
	stdin_isatty = _isatty(_fileno(stdin));
	stdout_isatty = _isatty(_fileno(stdout));
}

Out _out;
