#ifndef _USER_DATA_HH_
#define _USER_DATA_HH_

#include <list>
#include "eqparser.hh"

namespace user_data {

	typedef std::list<struct eqparser::_eq*> _system;

	struct _userdata {
		struct eqparser::_eq func;
		_system system;
	};

	void get_data_from_user(struct _userdata*);

} // namespace user_data

#endif
