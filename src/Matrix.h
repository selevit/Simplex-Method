#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstdlib>
#include <cstring>
#include <iostream>

#define err(no) std::cerr << "Oops! Something went wrong." << std::endl; exit(no);

class matrix {
	private:
		double *buf;
		unsigned int x, y;
	public:
		matrix(unsigned int _x, unsigned int _y);
		~matrix();
		double* operator[](unsigned int i);
};

#endif /* _MATRIX_H_ */
