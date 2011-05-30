#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cmath>
#include <iostream>

#include "eqparser.h"

#define isnum(x) (x >= '0' && x <= '9')
#define iseqsign(x) (x == '<' || x == '=' || x == '>')
#define isarithsign(x) (x == '+' || x == '-')

namespace eqparser {

enum _type { none, num, arith_sign, eq_sign, x, end, space, min_max, approach };

struct _token {
	double num;
	enum _type type;
	enum _eqsign eqsign;
	enum _arithsign arithsign;
	enum _limit l;
};

static bool compare_vars(struct var& a, struct var& b) { return a.b < b.b; }

const char* parse(const char* s, struct _eq* eq, unsigned int* err_pos, enum _eqtype eqtype)
{
	_vars::iterator it;
	struct var _t;
	double t;
	enum { start, start_as, a, at_x, b, c, es, as, es_c, at_approach, at_lim } whereami;
	unsigned int i;
	bool found_match;
	char _x;
	_token tok;
	enum { _none, win, fail } result;
	const char* err;

	eq->vars.clear();
	_x = 0;
	err = 0;
	i = 0;
	whereami = start;
	found_match = false;
	result = _none;
	for (;;) {
		*err_pos = i+1;
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
// TODO: если &s[i] == "0x1", то atof возвращает 1
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

		if (tok.type == none && (strncmp(&s[i], "->", 2) == 0 || strncmp(&s[i], "=>", 2) == 0)) {
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
				_t.a = 1;
				whereami = at_x;
				break;
			}

			err = "ожидался пробел, число, арифметический знак или х";
			result = fail;
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

			err = "ожидалось число или х";
			result = fail;
			break;
		case a: // x
			if (tok.type == x) {
				whereami = at_x;
				break;
			}

			err = "ожидался х";
			result = fail;
			break;
		case at_x:
			if (tok.type == num) {
				whereami = b;
				if (_t.a < 0.00001)
					break;

				t = fabs(tok.num - (int)tok.num);
				if (t != 0 && t > 0.00001) {
					err = "индекс х не может быть дробным";
					result = fail;
					break;
				}
				_t.b = tok.num;

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

			err = "ожидался индекс х";
			result = fail;
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
					err = "не допускается использовать < или >";
					result = fail;
					break;
				}
				eq->sign = tok.eqsign;
				break;
			}

			if (eqtype == ineq)
				err = "ожидался пробел, арифметический знак или знак сравнения после индекса";
			if (eqtype == func)
				err = "ожидался пробел, арифметический знак или знак стремления (->) после индекса";
			result = fail;
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

			err = "ожидался пробел или лимит (min/max) после ->";
			result = fail;
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

			err = "ожидался пробел, число или х";
			result = fail;
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

			err = "ожидался пробел, знак минус или число";
			result = fail;
			break;
		case es_c:
			if (tok.type == num) {
				whereami = c;
				eq->rval *= tok.num;
				break;
			}

			err = "ожидалось число";
			result = fail;
			break;
		case c:
			if (tok.type == space) {
				break;
			}
			if (tok.type == end) {
				result = win;
				break;
			}

			err = "ожидался пробел или конец строки";
			result = fail;
			break;
		case at_lim:
			if (tok.type == space) {
				break;
			}
			if (tok.type == end) {
				result = win;
				break;
			}

			err = "ожидался пробел или конец строки";
			result = fail;
			break;
		}

		if (result == fail || result == win)
			break;
	}

	if (result == win) {
		for (it = eq->vars.begin(); it != eq->vars.end();) {
			if ((*it).a == 0) {
				it = eq->vars.erase(it);
				continue;
			} else it++;
		}

		if (eq->vars.empty())
			err = "в левой части неравенства должна быть хотя бы одна переменная с коэффициентом отичным от нуля";
		else
			eq->vars.sort(compare_vars);
	}

	return err;
}

void recreate_ineq(struct _eq* eq, std::string* s, enum _eqtype et)
{
	std::stringstream ss;
	_vars::iterator it;

	for (it = eq->vars.begin(); it != eq->vars.end(); it++) {
		if (it == eq->vars.begin()) {
			if ((*it).a < 0 && fabs((*it).a == 1))
				ss << "-";
		} else
			if ((*it).a > 0)
				ss << "+ ";
			else
				ss << "- ";
		if (fabs((*it).a) != 1)
			ss << fabs((*it).a);
		ss << "x" << (*it).b << " ";
	}
	if (et == func) {
		ss << "-> ";
		if (eq->l == max)
			ss << "max";
		else // eq->l == min
			ss << "min";
	} else { // et == ineq
		switch (eq->sign) {
		case equal:
			ss << "= ";
			break;
		case le:
			ss << "<= ";
			break;
		case ge:
			ss << ">= ";
			break;
		default:
			break;
		}
		ss << eq->rval;
	}

	*s = ss.str();
}

} // namespace eqparser
