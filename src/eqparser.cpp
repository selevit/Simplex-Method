#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "eqparser.h"

#define isnum(x) (x >= '0' && x <= '9')
#define iseqsign(x) (x == '<' || x == '=' || x == '>')
#define isarithsign(x) (x == '+' || x == '-')

namespace eqparser {

enum _type { none, num, arith_sign, eq_sign, x, end, space, min_max, approach };
enum _arithsign { minus, plus, mul, _div };

struct _token {
	double num;
	enum _type type;
	enum _eqsign eqsign;
	enum _arithsign arithsign;
	enum _limit l;
};

static bool compare_vars(struct var& a, struct var& b) { return a.b < b.b; }

const char* parse(const char* s, struct _eq* eq, enum _eqtype eqtype)
{
	_vars::iterator it;
	struct var _t;
	double t;
	enum { start, start_as, a, at_x, b, c, es, as, es_c, at_approach, at_lim } whereami;
	unsigned int i;
	bool win, found_match;
	const char* fail;
	char _x;
	_token tok;

	_x = 0;
	i = 0;
	whereami = start;
	found_match = false;
	fail = 0; win = false;
	for (;;) {
		tok.type = none;

		while (s[i] == ' ' || s[i] == '\t') {
			tok.type = space;
			i++;
		}

		if (s[i] == '\0' || s[i] == '\n') {
			i++;
			tok.type = end;
		}

		if (tok.type == none && isnum(s[i])) {
			tok.type = num; 
			for (tok.num = atof(&s[i]); isnum(s[i]) || s[i] == '.'; i++);
		}

		if (tok.type == none) {
			if (strcmp(&s[i], "min") == 0) {
				tok.type = min_max;
				tok.l = min;
				i += 3;
			} else if (strcmp(&s[i], "max") == 0) {
				tok.type = min_max;
				tok.l = max;
				i += 3;
			}
		}

		if (tok.type == none) {
			if (_x == 0) {
				if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
					_x = s[i];
					tok.type = x;
					i++;
				}
			} else {
				if (_x == s[i]) {
					tok.type = x;
					i++;
				}
			}
		}

		if (tok.type == none && strncmp(&s[i], "->", 2) == 0) {
			tok.type = approach;
			i += 2;
		}

		if (tok.type == none && iseqsign(s[i])) {
			tok.type = eq_sign;
			switch (s[i]) {
			case '<':
				tok.eqsign = lt;
				i++;
				if (s[i] == '=') {
					tok.eqsign = le;
					i++;
				}
				break;
			case '>':
				tok.eqsign = gt;
				i++;
				if (s[i] == '=') {
					tok.eqsign = ge;
					i++;
				}
				break;
			case '=':
				tok.eqsign = equal;
				i++;
				break;
			}
		}

		if (tok.type == none && isarithsign(s[i])) {
			tok.type = arith_sign;
			switch (s[i]) {
			case '+':
				tok.arithsign = plus;
				i++;
				break;
			case '-':
				tok.arithsign = minus;
				i++;
				break;
			}
		}

		if (tok.type == none) {
			fail = "Unallowed character detected";
		}

		switch (whereami) {
		case start: // space, arith_sign, num, x
			if (tok.type == space) {
				break;
			}
			if (tok.type == num) {
				_t.a = tok.num;
				whereami = a;
				break;
			}
			if (tok.type == arith_sign) {
				if (tok.arithsign == minus)
					_t.a = -1;
				else
					_t.a = 1;
				whereami = start_as;
				break;
			}
			if (tok.type == x) {
				whereami = at_x;
				break;
			}

			fail = "Expected space/tab, num, sign or x at the beginning";
			break;
		case start_as: // num
			if (tok.type == num) {
				whereami = a;
				_t.a *= tok.num;
				break;
			}
			if (tok.type == x) {
				whereami = at_x;
				break;
			}

			fail = "Unexpected token after start_as";
			break;
		case a: // x
			if (tok.type == x) {
				whereami = at_x;
				break;
			}

			fail = "You can't put anything besides x after a";
			break;
		case at_x:
			if (tok.type == num) {
				whereami = b;
				t = fabs(tok.num - (int)tok.num);
				if (t != 0 && t > 0.00001) {
					fail = "index can't be fractional";
					break;
				}
				_t.b = (unsigned int)tok.num;

				if (eq->vars.empty()) {
					eq->vars.push_back(_t);
				} else {
					for (it = eq->vars.begin(); it != eq->vars.end(); it++) {
						if ((*it).b == _t.b) {
							(*it).a += _t.a;
							found_match = true;
							break;
						}
					}
					if (!found_match) {
						eq->vars.push_back(_t);
					}
					found_match = false;
				}
				break;
			}

			fail = "You must put index after x";
			break;
		case b: // space, arith_sign, eq_sign
			if (tok.type == space) {
				break;
			}
			if (tok.type == arith_sign) {
				whereami = as;
				if (tok.arithsign == minus) 
					_t.a = -1;
				else
					_t.a = 1;
				break;
			}
			if (eqtype == func && tok.type == approach) {
				whereami = at_approach;
				break;
			}
			if (eqtype == ineq && tok.type == eq_sign) {
				whereami = es;
				eq->rval = 1;
				if (tok.eqsign == lt || tok.eqsign == gt) {
					fail = "You can't use < or >";
					break;
				}
				eq->sign = tok.eqsign;
				break;
			}

			fail = "Only space, arith_sign or eq_sign is allowed after b";
			break;
		case at_approach:
			if (tok.type == space) {
				break;
			}
			if (tok.type == min_max) {
				whereami = at_lim;
				eq->l = tok.l;
				break;
			}

			fail = "Expected ether space or limit after ->";
			break;
		case as: // space, num, x
			if (tok.type == space) {
				break;
			}
			if (tok.type == num) {
				whereami = a;
				_t.a *= tok.num;
				break;
			}
			if (tok.type == x) {
				whereami = at_x;
				break;
			}

			fail = "Unexpected token after as";
			break;
		case es: // space, num, arith_sign
			if (tok.type == space) {
				break;
			}
			if (tok.type == arith_sign) {
				whereami = es_c;
				if (tok.arithsign == minus)
					eq->rval = -1;
				break;
			}
			if (tok.type == num) {
				whereami = c;
				eq->rval = tok.num;
				break;
			}

			fail = "You can only put space or rvalue after equalty sign";
			break;
		case es_c:
			if (tok.type == tok.num) {
				whereami = c;
				eq->rval *= tok.num;
				break;
			}

			fail = "You can't put anything between a sign and c";
			break;
		case c:
			if (tok.type == space) {
				break;
			}
			if (tok.type == end) {
				win = true;
				break;
			}

			fail = "Nothing allowed after c";
			break;
		case at_lim:
			if (tok.type == space) {
				break;
			}
			if (tok.type == end) {
				win = true;
				break;
			}

			fail = "Nothing allowed after limit";
			break;
		}

		if (fail || win)
			break;
	}

	if (win) {
		for (it = eq->vars.begin(); it != eq->vars.end();) {
			if ((*it).a == 0) {
				it = eq->vars.erase(it);
				continue;
			} else it++;
		}

		if (eq->vars.empty())
			fail = "There must be at least one variable with a that isn't null";
		else
			eq->vars.sort(compare_vars);
	}

	return fail;
}

} // namespace eqparser
