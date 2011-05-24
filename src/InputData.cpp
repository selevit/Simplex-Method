#include <iostream>
#include <fstream>
#include <string>
#include "InputData.h"
#include "Out.h"

void InputData::getAndSetInputData()
{
	if (!_out.stdin_is_a_terminal)
		_out.can_output = false;

	setNumOfSourceVars();
	Init(numOfSourceVars);
	setFactorsOfTargetFunctionVars();
	setWayOfTargetFunction();
	setFactorsOfSystemVars();
	setFreeMembersOfSystem();

	if (!_out.stdin_is_a_terminal)
		_out.can_output = true;
}

void InputData::setFreeMembersOfSystem()
{
	for (int i = 0; i < numOfSourceVars; ++i)
	{
		_out << std::cout << "Введите значение свободного члена для " << i + 1 << "-го неравенства: ";
// TODO: вот это сегфолтнется, если долбоюзер введёт букву
		std::cin >> freeMembersOfSystem[i];
	}
	_out << std::cout << "\n";
}

void InputData::setFactorsOfSystemVars()
{
	int i, j;

	for (i = 0; i < numOfSourceVars; ++i)
	{
		for (j = 0; j < numOfSourceVars; ++j)
		{
			_out << std::cout << "Введите коэффициент при X" << j + 1 << " для " << i + 1 << "-го неравенства: ";
// аналогично
			std::cin >> (*factorsOfSystemVars)[i][j];
		}
		_out << std::cout << "\n";
	}
}

void InputData::setFactorsOfTargetFunctionVars()
{
	_out << std::cout << "\n";
	for (int i = 0; i < numOfSourceVars; ++i)
	{
		_out << std::cout << "Введите коэффициент целевой функции при X" << i + 1 << ": ";
// аналогично
		std::cin >> factorsOfTargetFunctionVars[i];
	}
	_out << std::cout << "\n";
}

void InputData::setNumOfSourceVars()
{
	for (numOfSourceVars = 0; numOfSourceVars <= 0;) {
		_out << std::cout << "Введите количество основных переменных задачи (> 0): ";
		std::cin >> numOfSourceVars;
	}
}

void InputData::setWayOfTargetFunction()
{
	std::string MaxOrMin;

	while (MaxOrMin.compare("max") != 0 && MaxOrMin.compare("min")) {
		_out << std::cout << "Введите направление целевой функции (max, min): ";
		std::cin >> MaxOrMin;
		if (MaxOrMin.compare("max") == 0)
			wayOfTargetFunction = true;
		else if (MaxOrMin.compare("min") == 0)
			wayOfTargetFunction = false;
	}
	_out << std::cout << "\n";
}

void InputData::Init(unsigned int vars)
{
	freeMembersOfSystem = new double[vars];
	factorsOfSystemVars = new matrix(vars, vars);
	factorsOfTargetFunctionVars = new double[vars];
}
