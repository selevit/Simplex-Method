#ifndef _MATRIX_HH_
#define _MATRIX_HH_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Matrix.hh"

#define err(no) std::cerr << "Oops! Something went wrong." << std::endl; exit(no);

template <class T>
class matrix {
	private:
		T *buf;
		unsigned int x, y, size;
	public:
		matrix(unsigned int _x, unsigned int _y);
		T* operator[](unsigned int i);
		void operator=(matrix& m);
};

template <class T>
matrix<T>::matrix(unsigned int _x, unsigned int _y) : x(_x), y(_y), size(_x*_y)
{
//	std::cerr << "Allocating memory for [" << x << "][" << y << "]" << std::endl;
	if ( size <=0 ) {
		err(20);
	}
	buf = new T[size];
}

template <class T>
T* matrix<T>::operator[](unsigned int i)
{
//	std::cerr << i << " " << x << " " << y << " " << size << std::endl;
	if (i >= x) {
		err(22);
	}
	return buf+(y*i);
}

template <class T>
void matrix<T>::operator=(matrix<T>& m)
{
	if (m.x != x || m.y != y) {
		err(21);
	}
	memcpy(buf, m.buf, size*sizeof(T));
}


#endif /* _MATRIX_HH_ */
