#include <iostream>
#include <string>
#include <sstream>

#include "eqparser.h"

int main()
{
	using namespace eqparser;

	std::string s;
	std::stringstream err;
	struct _eq* eq;
	_vars::iterator it;
	enum _eqtype t;

	eq = new struct _eq;
	t = func;
	getline(std::cin, s);
	
	bool g = parse(s.c_str(), eq, err, t);

	if (!g)
		std::cout << err.str() << std::endl;
	else { // win
		for (it = eq->vars.begin(); it != eq->vars.end(); it++)
			std::cout << "a: " << (*it).a << ", b: " << (*it).b << std::endl;
		if (t == ineq)
			std::cout << "sign: " << eq->sign << ", rvalue: " << eq->rval << std::endl;
		else // func
			std::cout << "limit: " << eq->l << std::endl;
	}

	return 0;
}
