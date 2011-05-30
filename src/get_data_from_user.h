#ifndef _GET_DATA_FROM_USER_H_
#define _GET_DATA_FROM_USER_H_

#include <list>
#include "eqparser.h"

struct _userdata {
	struct eqparser::_eq func;
	std::list<struct eqparser::_eq*> system;
};

void get_data_from_user(struct _userdata*);

#endif
