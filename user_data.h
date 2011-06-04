#ifndef _USER_DATA_H_
#define _USER_DATA_H_

class user_data {
	public:
		void get_data_from_user();
		void user_data_is_valid();
	protected:
		double *function;
		double *fm;
		double **system;
	 	int *sign;
		int num_v;
		int num_l;
		bool way;
};

#endif /* _USER_DATA_H_ */
