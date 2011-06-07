#ifndef _CELLS_HH_
#define _CELLS_HH_

#include "fraction.hh"

namespace cells {

	class cell /* this is an interface class */
	{
	public:
		virtual cell& operator=(double);
		virtual cell& operator=(int);
		virtual cell& operator=(cell&);
		virtual cell& operator-=(cell&);
		virtual cell replicate();
	};

	class var : public cell
	{
		fraction::fraction frac;
	public:
		void init(int, int = 0); // this is silly temporary hack
		virtual var& operator=(double);
		virtual var& operator=(int);
	};

	class bigm : public cell
	{
		fraction::fraction mfactor, frac;
	public:
		void init(int, int);
	};

	template <class T>
	class border : public cell
	{
	public:
		border(char, unsigned int);
		char var_name;
		unsigned int var_index;
		T value; // bigm или var
	};

	template <class T>
	border<T>::border(char name, unsigned int index)
	{
		var_name = name;
		var_index = index;

		switch (name) {
		case 'm':
			value.init(-1, 0);
			break;
		case 's':
		case 'x':
			value.init(0, 0);
			break;

		};
	}

} /* namespace cells */

#endif /* _CELLS_HH_ */
