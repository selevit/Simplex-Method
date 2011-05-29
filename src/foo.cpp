#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <list>
#include <cmath>

#define isnum(x) (x >= '0' && x <= '9')
#define iseqsign(x) (x == '<' || x == '=' || x == '>')
#define isarithsign(x) (x == '+' || x == '-')

struct var { double a; unsigned int b; };

bool compare_vars(struct var& a, struct var& b) { return a.b < b.b; }

int main()
{
	// const char* s = "4531.129x1 + 43.11x1 + 2.1x1 = -100";
	char s[100];
	std::cin.getline(s, 100);

	enum _eqsign { le, lt, eq, gt, ge }; // <= < = > >=

	struct {
		double _num; 
		enum { none, num, arith_sign, eq_sign, x, end, space } type;
		enum { minus, plus } _arith_sign;
		enum _eqsign _eq_sign;
	} tok;
	std::list<struct var> equations;
	std::list<struct var>::iterator eq_it, t_it;
	enum _eqsign this_eq_sign;
	double rvalue, t;
	struct var _t;
	// -10x1 >= 100; as a x b es c
	enum { start, start_as, a, x, b, c, es, as, es_c } whereami;
	unsigned int i;
	bool win, found_match;
	const char* fail;
	char _x;

	_x = 0;
	i = 0;
	whereami = start;
	found_match = false;
	fail = 0; win = false;
	for (;;) {
		tok.type = tok.none;

		while (s[i] == ' ' || s[i] == '\t') {
			tok.type = tok.space;
			i++;
		}

		if (s[i] == '\0' || s[i] == '\n') {
			i++;
			tok.type = tok.end;
		}

		if (tok.type == tok.none && isnum(s[i])) {
			tok.type = tok.num; 
			for (tok._num = atof(&s[i]); isnum(s[i]) || s[i] == '.'; i++);
		}

		if (tok.type == tok.none) {
			if (_x == 0) {
				if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
					_x = s[i];
					tok.type = tok.x;
					i++;
				}
			} else {
				if (_x == s[i]) {
					tok.type = tok.x;
					i++;
				}
			}
		}

		if (tok.type == tok.none && iseqsign(s[i])) {
			tok.type = tok.eq_sign;
			switch (s[i]) {
			case '<':
				tok._eq_sign = lt;
				i++;
				if (s[i] == '=') {
					tok._eq_sign = le;
					i++;
				}
				break;
			case '>':
				tok._eq_sign = gt;
				i++;
				if (s[i] == '=') {
					tok._eq_sign = ge;
					i++;
				}
				break;
			case '=':
				tok._eq_sign = eq;
				i++;
				break;
			}
		}

		if (tok.type == tok.none && isarithsign(s[i])) {
			tok.type = tok.arith_sign;
			switch (s[i]) {
			case '+':
				tok._arith_sign = tok.plus;
				i++;
				break;
			case '-':
				tok._arith_sign = tok.minus;
				i++;
				break;
			}
		}

		if (tok.type == tok.none) {
			fail = "Unallowed character detected";
		}

		switch (whereami) {
		case start: // space, arith_sign, num, x
			if (tok.type == tok.space) {
				break;
			}
			if (tok.type == tok.num) {
				_t.a = tok._num;
				whereami = a;
				break;
			}
			if (tok.type == tok.arith_sign) {
				if (tok._arith_sign == tok.minus)
					_t.a = -1;
				else
					_t.a = 1;
				whereami = start_as;
				break;
			}
			if (tok.type == tok.x) {
				whereami = x;
				break;
			}

			fail = "Expected space/tab, num, sign or x at the beginning";
			break;
		case start_as: // num
			if (tok.type == tok.num) {
				whereami = a;
				_t.a *= tok._num;
				break;
			}
			if (tok.type == tok.x) {
				whereami = x;
				break;
			}

			fail = "Unexpected token after start_as";
			break;
		case a: // x
			if (tok.type == tok.x) {
				whereami = x;
				break;
			}

			fail = "You can't put anything besides x after a";
			break;
		case x:
			if (tok.type == tok.num) {
				whereami = b;
				t = fabs(tok._num - (int)tok._num);
				if (t != 0 && t > 0.00001) {
					fail = "index can't be fractional";
					break;
				}
				_t.b = (unsigned int)tok._num;

				if (equations.empty()) {
					equations.push_back(_t);
				} else {
					for (eq_it = equations.begin(); eq_it != equations.end(); eq_it++) {
						if ((*eq_it).b == _t.b) {
							(*eq_it).a += _t.a;
							found_match = true;
							break;
						}
					}
					if (!found_match) {
						equations.push_back(_t);
					}
					found_match = false;
				}
				break;
			}

			fail = "You must put index after x";
			break;
		case b: // space, arith_sign, eq_sign
			if (tok.type == tok.space) {
				break;
			}
			if (tok.type == tok.arith_sign) {
				whereami = as;
				if (tok._arith_sign == tok.minus) 
					_t.a = -1;
				else
					_t.a = 1;
				break;
			}
			if (tok.type == tok.eq_sign) {
				whereami = es;
				rvalue = 1;
				if (tok._eq_sign == lt || tok._eq_sign == gt) {
					fail = "You can't use < or >";
					break;
				}
				this_eq_sign = tok._eq_sign;
				break;
			}

			fail = "Only space, arith_sign or eq_sign is allowed after b";
			break;
		case as: // space, num, x
			if (tok.type == tok.space) {
				break;
			}
			if (tok.type == tok.num) {
				whereami = a;
				_t.a *= tok._num;
				break;
			}
			if (tok.type == tok.x) {
				whereami = x;
				break;
			}

			fail = "Unexpected token after as";
			break;
		case es: // space, num, arith_sign
			if (tok.type == tok.space) {
				break;
			}
			if (tok.type == tok.arith_sign) {
				whereami = es_c;
				if (tok._arith_sign == tok.minus)
					rvalue = -1;
				break;
			}
			if (tok.type == tok.num) {
				whereami = c;
				rvalue = tok._num;
				break;
			}

			fail = "You can only put space or rvalue after equalty sign";
			break;
		case es_c:
			if (tok.type == tok.num) {
				whereami = c;
				rvalue *= tok._num;
				break;
			}

			fail = "You can't put anything between a sign and c";
			break;
		case c:
			if (tok.type == tok.space) {
				break;
			}
			if (tok.type == tok.end) {
				win = true;
				break;
			}

			fail = "Nothing allowed after c";
			break;
		}

		if (fail || win)
			break;
	}

	if (win) {
		for (eq_it = equations.begin(); eq_it != equations.end();) {
			if ((*eq_it).a == 0) {
				eq_it = equations.erase(eq_it);
				continue;
			} else eq_it++;
		}

		if (equations.empty())
			fail = "There must be at least one variable with a that isn't null";
		else
			equations.sort(compare_vars);
	}

	if (fail)
		std::cout << fail << std::endl;
	else { // win
			std::cout << "succeded" << std::endl;
		for (eq_it = equations.begin(); eq_it != equations.end(); eq_it++)
			std::cout << "a: " << (*eq_it).a << ", b: " << (*eq_it).b << std::endl;
		std::cout << "sign: " << this_eq_sign << ", rvalue: " << rvalue << std::endl;
	}

	return 0;
}
