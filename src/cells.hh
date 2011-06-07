#ifndef _CELLS_HH_
#define _CELLS_HH_

#include "fraction.hh"

namespace cells {

	class bigm
	{
		fraction::fraction mfactor;
	};

	class cell 
	{
	public:
		cell& operator=(float);
		virtual cell& operator=(cell&);
		virtual cell& operator-=(cell&);
//		virtual std::string str() = 0;
	};

	class var : public cell	
	{
		fraction::fraction frac;
	public:
		var& operator=(int x) { frac = x; return *this; }
	};

	class bigm_var : public bigm, public cell 
	{
		
	};

	template <class T>
	class border : public cell 
	{
	public:
		char var_name;
		unsigned int var_index;
		T value; // bigm или fraction
	border(char name, unsigned int index) : var_name(name), var_index(index) {};
	};

} /* namespace cells */

#endif /* _CELLS_HH_ */
