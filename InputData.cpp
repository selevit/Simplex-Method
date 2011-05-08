#include <iostream>

#include <string>

#include "InputData.h"


void InputData::getAndSetInputData()
{
	setNumOfSourceVars();
	setFactorsOfTargetFunctionVars();
	setFactorsOfSystemVars();
	setFreeMembersOfSystem();
}

double * InputData::getFreeMembersOfSystem()
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

void InputData::setFreeMembersOfSystem ()
{
	freeMembersOfSystem = getFreeMembersOfSystem();
}

double ** InputData::getFactorsOfSystemVars()
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

void InputData::setFactorsOfSystemVars()
{
	factorsOfSystemVars = getFactorsOfSystemVars();	
}

double * InputData::getFactorsOfTargetFunctionVars()
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

void InputData::setFactorsOfTargetFunctionVars()
{
	factorsOfTargetFunctionVars =  getFactorsOfTargetFunctionVars();
}

int InputData::getNumOfSourceVars()
{
	int result;
	std::cout << "Введите количество основных переменных задачи: ";
	std::cin >> result;
	return result;
}

bool InputData::setNumOfSourceVars()
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

void InputData::error(int numberOfError)
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
