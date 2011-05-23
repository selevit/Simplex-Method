#ifndef _USER_DATA_H_
#define _USER_DATA_H_

#include "Matrix.h"

class UserData {
public:
       /*
	    *  Коэффициенты переменных
	    *  целевой функции
	    */

		double * factorsOfTargetFunctionVars;
		
		/*
		 * Коэффициенты переменных при
		 * системе неравенств
		*/

		matrix* factorsOfSystemVars;

		/*
		 * Значения свободных членов
		 * про системе неравенств
		*/

		double * freeMembersOfSystem;

		UserData(unsigned int vars)
		{
			freeMembersOfSystem = new double[vars];
			factorsOfSystemVars = new matrix(vars, vars);
			factorsOfTargetFunctionVars = new double[vars];
		}

		~UserData()
		{
			delete[] freeMembersOfSystem;
			delete factorsOfSystemVars;
			delete factorsOfTargetFunctionVars;
		}
};

#endif
