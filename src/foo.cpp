#include <iostream>
#include <string>

#include "eqparser.h"

int main()
{
	using namespace eqparser;

	std::string s;
	struct _eq* eq;
	_vars::iterator it;
	enum _eqtype t;

	eq = new struct _eq;
	t = func;
	getline(std::cin, s);
	
	const char* f = parse(s.c_str(), eq, t);

	if (f)
		std::cout << f << std::endl;
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
