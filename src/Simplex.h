#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_ 1


#include <iostream>

#include "InputData.h"
#include "Plane.h"
#include "SubPlane.h"


/*
 * В этом файле содержится класс, элементы которого
 * содержат все элементы симплекс таблицы, а функции
 * этого класса расчитывают оптимальный план задачи.
*/

class Simplex : public InputData  {

	public:
		
		/* Данная функция
		 * Задает значения членам класса
		 * для первого опорного плана
		*/

		void init();

		/*
		 * Данная функция задает значения для
		 * всех элементов текущего плана.
		 * Из нее вызываются функции, которые
		 * задают конкретные значения для отдельных
		 * элементов текущего плана в симплекс таблице.
		*/

		int setValues();

		/*
		 * Данная фукнция проверяет полученный план
		 * на оптимальность.
		*/
		
		bool checkThColumn();

		bool checkPlane();

		/*
		 * Данная функция задает значения базисных
		 * переменных в симплекс таблице
		*/

		void setBasisVars(int numOfIteration);

		/*
		 * Данная фукнция отображает решение задачи.
		*/

		void printOutData(int numOfIteration);

		void displayResult(int numOfIteration);		

		/*
		 * Данная функция задаен значения коэффициентов
		 * при основных и базисных переменных в симплекс таблице.
		*/
		
		void setFactorsOfVars(int numOfIteration);

		/*
		 * Данная фукнция задает значения коэффициетов
		 * в индексной строке симплекс таблицы.
		*/

		void setIndexString(int numOfIteration);

		/*
		 * Данная функция задает значение фукнции
		 * цели в симплекс таблице.
		*/

		void setTargetFunction(int numOfIteration);

		/*
		 * Данная функция задает значения коэффициентов
		 * последнего столбца симплексной таблицы.
		*/

		void setThColumn();

		/*
		 * Данная функция задает значение индекса ведущего
		 * столбца текущего плана симплексной таблицы.
		*/

		void setIndexOfLeavingColumn();

		/*
		 * Данная функция задает значение индекса ведущей
		 * строки текущего плана симплексной таблицы.
		*/

		void setIndexOfLeavingRow();

		/*
		 * Данная функция находит значение
		 * разрешающего элемента и возвращает его
		*/

		void setAllowingMember();

	private:
		Plane<double> *currentPlane, *bestPlane;
		SubPlane<double> *tmp;
};

/*где-то в конце итерации

if (error() || finished()) {
	print(best);
}
if (better(current, best)) {
	best = current;
}
*/


#endif
