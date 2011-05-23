#ifndef _PLANE_H_
#define _PLANE_H_

#include "Matrix.h"

class Plane {
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

	/*
	 * Индексная строка симплексной таблицы
	*/

	double * indexString;

 	/*
	 * Значения базисных переменных
	 * в симплекс теблице.
	*/

	matrix* basisVars;

	/*
	 * Коэффициенты при  переменных
	 * в симплекс-таблице.
	*/

	matrix* varsFactors;

	Plane(unsigned int vars)
	{
		thColumn = new double[vars];
		targetFunction = 0;
		basisVars = new matrix(2, vars);
		varsFactors = new matrix(vars, vars*2);
		indexString = new double[vars*2];
	}
};

#endif /* _PLANE_H_ */
