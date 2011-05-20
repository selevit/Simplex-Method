#include "Matrix.h"

matrix::matrix(unsigned int _x, unsigned int _y) : x(_x), y(_y) {
	if ( _x <= 0 || _y <= 0 ) {
		err(20);
	}
	buf = new double[_x * _y];
}

double* matrix::operator[](unsigned int i) {
	if (i >= x) {
		err(22);
	}
	return buf+(y*i);
}

matrix::~matrix() {
	delete[] buf;
}
