#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#define isnum(x) (x >= '0' && x <= '9')
#define iseqsign(x) (x == '<' || x == '=' || x == '>')
#define isarithsign(x) (x == '+' || x == '-')

int main()
{
	const char* s = "-2x3     + x4-x5<=20";

	struct {
		int _num; 
		enum { none = 1<<0, num = 1<<1, arith_sign = 1<<2, eq_sign = 1<<3, x = 1<<4, end = 1<<5 } type;
		enum { minus, plus } _arith_sign;
		enum { le, lt, eq, gt, ge } _eq_sign; // <= < = > >=
	} tok;
	unsigned char expect;
	unsigned int i;

	i = 0;
	expect = 0 | tok.arith_sign | tok.num | tok.x;
	for (;;) {
		tok.type = tok.none;

		for (; s[i] == ' ' || s[i] == '\t';	i++);

		if (s[i] == '\0' || s[i] == '\n') {
			i++;
			tok.type = tok.end;
		}

		if (tok.type == tok.none && isnum(s[i])) {
			tok._num = 0;
			tok.type = tok.num; 
			for (; isnum(s[i]); i++) {
				tok._num = tok._num*10 + atoi(&s[i]);
			}
		}

		if (tok.type == tok.none && s[i] == 'x') {
			tok.type = tok.x;
			i++;
		}

		if (tok.type == tok.none && iseqsign(s[i])) {
			tok.type = tok.eq_sign;
			switch (s[i]) {
			case '<':
				tok._eq_sign = tok.lt;
				i++;
				if (s[i] == '=') {
					tok._eq_sign = tok.le;
					i++;
				}
				break;
			case '>':
				tok._eq_sign = tok.gt;
				i++;
				if (s[i] == '=') {
					tok._eq_sign = tok.ge;
					i++;
				}
				break;
			case '=':
				tok._eq_sign = tok.eq;
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

		if (expect & tok.type) {
			switch(tok.type) {
			case tok.arith_sign:
				expect = tok.num | tok.x;
				break;
			case tok.num:
				expect = tok.num | tok.x | tok.arith_sign | tok.eq_sign;
				break;
			case tok.eq_sign:
				expect = tok.num;
				break;
			case tok.x:
				expect = tok.num;
				break;
			}
		}




//		std::cout << tok.type << " ";
		if (tok.type == tok.end) {
			break;
		}
	}
//	std::cout << std::endl;

	return 0;
}
