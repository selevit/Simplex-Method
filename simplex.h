#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_

#include <sstream>

#include "user_data.h"

class simplex : public user_data {
	public:
		void init();
		void gen_plane();
		bool plane_is_valid();
		bool function_is_undefined();
		void print_result_to_file(int it_num);
	private:
		double func;
		double **bv;
		double **sv;
		double *istr;
		double *th;
		double alm;
		int i_lrow;
		int i_lcol;
		std::stringstream table;
};

#endif /* _SIMPLEX_H_ */
