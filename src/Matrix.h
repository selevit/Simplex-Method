#ifndef _MATRIX_H_
#define _MATRIX_H_

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
