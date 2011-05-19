#ifndef _PLANE_H_
#define _PLANE_H_

#include "SubPlane.h"

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

Plane(unsigned int _vars) : vars(_vars), SubPlane<T>(_vars)
	{
		thColumn = new double[vars];
		targetFunction = 0;
	}

	void operator=(Plane<T>& p)
	{
		targetFunction = p.targetFunction;
		memcpy(thColumn, p.thColumn, vars*sizeof(double));
		indexOfLeavingRow = p.indexOfLeavingRow;
		indexOfLeavingColumn = p.indexOfLeavingColumn;
		allowingMember = p.allowingMember;
		SubPlane<T>::operator=(p);
	}
private:
	unsigned int vars;
};

#endif /* _PLANE_H_ */
