#ifndef _PLANE_H_
#define _PLANE_H_

#include "SubPlane.h"

class Plane : public SubPlane {
public:
	/*
	 * Значение целевой функции
	*/

	double targetFunction;

	/*
	 * Последний столбец симплексной таблицы
	*/

	double * thColumn;
	
	/*
	 * Индекс ведущей строки.
	*/		
		
	int indexOfLeavingRow;
	
	/*
	 * Индекс ведущего столбца.
	*/
		
	int indexOfLeavingColumn;		
	
	/*
	 * Разрешающий элемент.
	*/

	double allowingMember;

Plane(unsigned int vars) : SubPlane(vars) {
		thColumn = new double[vars];
		targetFunction = 0;
	}
};

#endif /* _PLANE_H_ */
