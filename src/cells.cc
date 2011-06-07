#include "cells.hh"
#include <iostream>

namespace cells {

	cell& cell::operator=(double d)
	{
		std::cout << "cell::operator=(double d)" << std::endl;
		return *this;
	}

	cell& cell::operator=(int i)
	{
		std::cout << "cell::operator=(int i)" << std::endl;
		return *this;
	}

	cell& cell::operator=(cell& c)
	{
		std::cout << "cell::operator=(cell& c)" << std::endl;
		return *this;
	}

	cell& cell::operator-=(cell& c)
	{
		std::cout << "cell::operator-=(cell& c)" << std::endl;
		return *this;
	}

	cell cell::replicate()
	{
		std::cout << "trying to replicate through me, oh dear!" << std::endl;
		return *this;
	}
	
	var& var::operator=(double d)
	{
		frac = d;
		return *this;
	}

	var& var::operator=(int i)
	{
		frac = i;
		return *this;
	}

	void var::init(int f, int hack)
	{
		frac = f;
	}

	void bigm::init(int m, int f)
	{
		mfactor = m;
		frac = f;
	}

}
