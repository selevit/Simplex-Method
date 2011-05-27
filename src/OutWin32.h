#ifndef _OUTWIN32_H_
#define _OUTWIN32_H_

#include "OutBase.h"

class Out : public OutBase
{
	Out();
	Out& operator<<(const char*);
private:
	bool stdout_isatty;
	const char* utf8_to_cp866(const char*);
};

#endif
