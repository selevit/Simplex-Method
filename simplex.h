/*
 * Этот заголовочный файл содержаит
 * различные классы, объекты и функции которых
 * необходимы для реализации алгоритма
 * поставленной задачи. В данном содержатся
 * только прототипы функций-членов, сами же
 * функции находятся в файле simplex.cpp,
 * которых находится в этой же диррекстории
 */

/*
 * Этот класс содержит объекты, хранящие
 * в себе исходные данные задачи, такие как
 * Функция цели и система неравенств.
 */

#include <string>

class SourceData {
	public:
	
		/*
		 * Данная функция объединяет все функции
		 * данного класса, т.е. принимает и задает
		 * Входные данные для последующего решения
		 * Задачи.
		 */
		void getAndSetSourceData()
		{
			setNumOfSourceVars();
			setFactorsOfTargetFunctionVars();
			setFactorsOfSystemVars();
			setFreeMembersOfSystem();
		}

		/*
		 * Данная функция принимает все свободные члены
		 * системы неравенств и возвращает их значения
		 * в качестве указателя.
		 */
		double * getFreeMembersOfSystem()
		{
			double * freeMembers = new double [numOfSourceVars];
			for (int i = 0; i < numOfSourceVars; ++i)
			{
				std::cout << "Введите значение свободного члена для " << i + 1 << "-го неравенства: ";
				std::cin >> freeMembers [i];
			}
			std::cout << std::endl;
			return freeMembers;
		}
		
		/*
		 * Данная функция присваивает закрытому члену freeMembersOfSystem
		 * (Свободные члены системы неравенств) значения, полученные из
		 * функции getFreeMembersOfSystem
		 */
		void setFreeMembersOfSystem ()
		{
			freeMembersOfSystem = new double [numOfSourceVars];
			freeMembersOfSystem = getFreeMembersOfSystem();
		}

		/*
		 * Данная функция принимает все коэффициенты
		 * переменных системы неравенств и возвращает
		 * их значения в качестве указателя.
		 */
		double ** getFactorsOfSystemVars()
		{
			double ** factorsOfSystemVariables = new double * [numOfSourceVars];
			for (int i = 0; i < numOfSourceVars; ++i)
				factorsOfSystemVariables [i] = new double [numOfSourceVars];

			for (int i = 0; i < numOfSourceVars; ++i)
			{
				for (int j = 0; j < numOfSourceVars; ++j)
				{
					std::cout << "Введите коэффициент при X" << j + 1 << " для " << i + 1 << "-го неравенстве: ";
					std::cin >> factorsOfSystemVariables [i][j];
				}
				std::cout << std::endl;
			}
			return factorsOfSystemVariables;
		}

		/*
		 * Данная функция присваивает закрытому члену factorOfSystemVars
		 * (Коэффициенты переменных в системе неравенств) значение
		 * полученное из функции getFactorsOfSystemVars/
		 */
		void setFactorsOfSystemVars()
		{
			factorsOfSystemVars = new double * [numOfSourceVars];
			for (int i = 0; i < numOfSourceVars; ++i)
				factorsOfSystemVars[i] = new double [numOfSourceVars];
			factorsOfSystemVars = getFactorsOfSystemVars();	
		}

		/*
		 * Данная функция принимает коэффициенты
		 * переменных Целевой функции, введенные
		 * пользователем с клавиатуры и возвращает
		 * Указатель на эти значения.
		 */
		double * getFactorsOfTargetFunctionVars()
		{
			double * factorsOfTargetFunctionVariables  = new double [numOfSourceVars];
			std::cout << std::endl;
			for (int i = 0; i < numOfSourceVars; ++i)
			{
				std::cout << "Введите коэфициент целевой функции при X" << i + 1 << ": ";
				std::cin >> factorsOfTargetFunctionVariables [i];
			}
			std::cout << std::endl;
			return  factorsOfTargetFunctionVariables;
		}

		/*
		 * Данная функция задает значение, полученное из
		 * функции getFactorsOfTargetFunctionVars()
		 * закрытому члену factorsOfTargetFunctionVars.
		 */
		void setFactorsOfTargetFunctionVars()
		{
			factorsOfTargetFunctionVars = new double [numOfSourceVars];
			factorsOfTargetFunctionVars =  getFactorsOfTargetFunctionVars();
		}

		/*
		 * Данная фукнция принимает количество
		 * основных переменных задачи, введенное 
		 * пользователем с клавиатуры 
		 * и возвращает это значение.
		 */
		int getNumOfSourceVars()
		{
			int result;
			std::cout << "Введите количество основных переменных задачи: ";
			std::cin >> result;
			return result;
		}

		/*
		 * Данная функция задает закрытому члену класса
		 * NumOfSourceVars (Количество основных переменных
		 * задачи) Значение, которая возвращает функция
		 * getNumOfSourceVars()/
		 */
		bool setNumOfSourceVars()
		{
			int result = getNumOfSourceVars();
			if (result > 0)
			{
				numOfSourceVars = result;
				return true;
			}
			else
			{
				error(1);
				setNumOfSourceVars();
			}
		}

		/*
		 * Данная фукнция принимает целочисленный аргумент
		 * и возвращает пользователю ошибку, соответствующую
		 * этому аргументу.
		 */
		void error(int numberOfError)
		{
			std::string errorMessage;
			switch (numberOfError)
			{
				case 0:
					errorMessage = "Возникла непредвиненная ошибка. попробуйте еще раз."; 
					break;
				case 1:
					errorMessage = "Вы ввели недопустимое значение.";
					break;
			}
			std::cout << std::endl;
			std::cout << errorMessage;
			std::cout << std::endl << std::endl;;
		
		}
	private:

		/*
		 * Количество исходных переменных
		 * целевой функции и системы неравенств
		 */
		int numOfSourceVars; 

		/*
		 * Коэффициенты переменных
		 * целевой функции
	     */
		double *  factorsOfTargetFunctionVars;
		
		/*
		 * Коэффициенты переменных при
		 * системе неравенств
		 */
		double ** factorsOfSystemVars;

		/*
		 * Значения свободных членов
		 * про системе неравенств
		 */
		double * freeMembersOfSystem;
};
