#include <ostream>

#include "OutBase.h"

OutBase& OutBase::operator<<(int d)
{
	if (can_output)
		*p << d;

	return *this;
}

OutBase& OutBase::operator<<(std::ostream& s)
{
	p = &s;

	return *this;
}
