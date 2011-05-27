#ifndef _OUTLINUX_H_
#define _OUTLINUX_H_

#include "OutBase.h"

class Out : public OutBase
{
public:
	Out& operator<<(const char*);
	Out();
};

#endif
