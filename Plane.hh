#ifndef _PLANE_HH_
#define _PLANE_HH_

#include "SubPlane.hh"

template <class T>
class Plane : public SubPlane<T> {
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

	Plane(unsigned int vars) : SubPlane<T>(vars)
	{
		thColumn = new double[vars];
		targetFunction = 0;
	}
};

#endif /* _PLANE_HH_ */
