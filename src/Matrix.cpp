#include "Matrix.h"

matrix::matrix(unsigned int _x, unsigned int _y) : x(_x), y(_y), size(_x*_y)
{
	if ( size <=0 ) {
		err(20);
	}
	buf = new double[size];
}

double* matrix::operator[](unsigned int i)
{
	if (i >= x) {
		err(22);
	}
	return buf+(y*i);
}

void matrix::operator=(matrix& m)
{
	if (m.x != x || m.y != y) {
		err(21);
	}
	memcpy(buf, m.buf, size*sizeof(double));
}

matrix::~matrix()
{
	delete[] buf;
}
