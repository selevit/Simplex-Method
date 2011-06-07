#include "fraction.hh"

namespace fraction {

	std::string fraction::str()
	{
		ss.str("");
		if (!(numerator * 100 % denominator))
			ss << ((double)numerator / denominator);
		else
			ss << numerator << "/" << denominator;
		return ss.str();
	}

// TODO: это просто тупо
	fraction::fraction(int i)
	{
		operator=(i);
	}

	fraction& fraction::operator=(int i)
	{
		denominator = 1;
		numerator = i;
		return *this;
	}

// TODO: тупой и ещё тупее тупого
	fraction::fraction(double d)
	{
		operator=(d);
	}

	fraction& fraction::operator=(double d)
	{
		denominator = 100000;
		numerator = d * denominator;
		reduce();
		return *this;
	}

	uint_list fraction::factorize_int(int n)
	{
		uint_list factors;
		int i = 2;

		for(;;) {
			if (!(n >= i * 2))
				break;
			if(!(n % i)) {
				n = n / i;
				factors.push_back(i);
				i = 2;
			} else i++;
		}
		factors.push_back(n);
		factors.sort();

		return factors;
	}

	void fraction::reduce()
	{
		uint_list num = factorize_int(numerator);
		uint_list den = factorize_int(denominator);
		uint_list::iterator i, j;

		for (i = num.begin(); i != num.end(); ++i) {
			for (j = den.begin(); j != den.end();) {
				if ( *i == *j ) {
					numerator /= *i;
					i = num.erase(i);
					denominator /= *j;
					j = den.erase(j);
				} else ++j;
			}
		}
	}

} /* namespace fraction */
