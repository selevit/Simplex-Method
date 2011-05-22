#include <iostream>
#include <fstream>
#include <string>

#include "InputData.h"

void InputData::getAndSetInputData()
{
	setNumOfSourceVars();
	user_data = new UserData(numOfSourceVars);
	setFactorsOfTargetFunctionVars();
	setWayOfTargetFunction();
	setFactorsOfSystemVars();
	setFreeMembersOfSystem();
}

void InputData::setFreeMembersOfSystem()
{
	int i;

	for (i = 0; i < numOfSourceVars; ++i)
	{
		if (input_interactive)
			out << "Введите значение свободного члена для " << i + 1 << "-го неравенства: ";
		std::cin >> user_data->freeMembersOfSystem[i];
	}
	if (input_interactive)
		std::cout << "\n";
}

void InputData::setFactorsOfSystemVars()
{
	int i, j;

	for (i = 0; i < numOfSourceVars; ++i)
	{
		for (j = 0; j < numOfSourceVars; ++j)
		{
			if (input_interactive)
				out << "Введите коэффициент при X" << j + 1 << " для " << i + 1 << "-го неравенства: ";
			std::cin >> (*user_data->factorsOfSystemVars)[i][j];
		}
		if (input_interactive)
			std::cout << "\n";
	}
}

void InputData::setFactorsOfTargetFunctionVars()
{
	if (input_interactive)
		std::cout << "\n";
	for (int i = 0; i < numOfSourceVars; ++i)
	{
		if (input_interactive)
			out << "Введите коэффициент целевой функции при X" << i + 1 << ": ";
		std::cin >> user_data->factorsOfTargetFunctionVars[i];
	}
	if (input_interactive)
		std::cout << "\n";
}

void InputData::setNumOfSourceVars()
{
	if (input_interactive)
		out << "Введите количество основных переменных задачи: ";
	std::cin >> numOfSourceVars;
	if (numOfSourceVars <= 0)
		die(_("Вы ввели недопустимое значение"), 1);
}

void InputData::setWayOfTargetFunction()
{
	std::string MaxOrMin;

	if (input_interactive)
		out << "Введите направление целевой функции (max, min): ";
	std::cin >> MaxOrMin;
	if (MaxOrMin.compare("max") == 0)
		wayOfTargetFunction = true;
	else if (MaxOrMin.compare("min") == 0)
		wayOfTargetFunction = false;
	else
		die(_("Вы ввели недопустимое значение."), 2);
	if (input_interactive)
		std::cout << "\n";
}

