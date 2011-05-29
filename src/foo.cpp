#include <iostream>
#include <string>

#include "eqparser.h"

int main()
{
	std::string s;
	struct eqparser::_eq* eq;
	eqparser::_vars::iterator it;

	getline(std::cin, s);
	
	const char* f = eqparser::parse(s.c_str(), &eq);

	if (f)
		std::cout << f << std::endl;
	else { // win
		std::cout << "succeded" << std::endl;
		for (it = eq->vars.begin(); it != eq->vars.end(); it++)
			std::cout << "a: " << (*it).a << ", b: " << (*it).b << std::endl;
		std::cout << "sign: " << eq->sign << ", rvalue: " << eq->rval << std::endl;
	}

	return 0;
}
