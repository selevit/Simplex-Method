#ifndef _EQPARSER_H_
#define _EQPARSER_H_

#include <list>
#include <string>

namespace eqparser {
	enum _eqsign { le, lt, equal, gt, ge };

	struct var { double a; unsigned int b; };
	typedef std::list<struct var> _vars;
	enum _limit { max, min };
	enum _arithsign { minus, plus, mul, _div };

	struct _eq {
		_vars vars;
		enum _eqsign sign;
		enum _limit l;
		double rval;
	};

	enum _eqtype { ineq, func };

	const char* parse(const char*, struct _eq*, unsigned int*, enum _eqtype = ineq);
	void recreate_ineq(struct _eq*, std::string*, enum _eqtype);
}

#endif /* _EQPARSER_H_ */
