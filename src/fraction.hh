#ifndef _FRATION_HH_
#define _FRATION_HH_

#include <list>
#include <sstream>

namespace fraction {

	typedef std::list<unsigned int> uint_list;

	class fraction {
		int numerator, denominator;
		std::stringstream ss;
		void reduce();
		uint_list factorize_int(int);
	public:
		fraction() : numerator(0), denominator(1) {};
		explicit fraction(int);
		fraction& operator=(int);
		explicit fraction(double);
		fraction& operator=(double);
		std::string str();
	};

}

#endif /* _FRACTION_HH_ */
