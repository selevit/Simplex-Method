#ifndef _USER_DATA_H_
#define _USER_DATA_H_

#include <list>
#include "eqparser.h"

namespace user_data {

typedef std::list<struct eqparser::_eq*> _system;

struct _userdata {
	struct eqparser::_eq func;
	_system system;
};

void get_data_from_user(struct _userdata*);

} // namespace user_data

#endif
