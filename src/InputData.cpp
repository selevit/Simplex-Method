#include <iostream>
#include <fstream>
#include <string>

#include "InputData.h"

void InputData::getAndSetInputData()
{
	setNumOfSourceVars();
	user_input = new Plane(numOfSourceVars);
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
			std::cout << _("Введите значение свободного члена для ") << i + 1 << _("-го неравенства: ");
		std::cin >> user_data->basisVars[i];
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
				std::cout << _("Введите коэффициент при X") << j + 1 << _(" для ") << i + 1 << _("-го неравенства: ");
			std::cin >> (*user_input->varsFactors)[i][j];
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
			std::cout << _("Введите коэфициент целевой функции при X") << i + 1 << ": ";
		std::cin >> user_input->indexString[i];
	}
	if (input_interactive)
		std::cout << "\n";
}

void InputData::setNumOfSourceVars()
{
	if (input_interactive)
		std::cout << _("Введите количество основных переменных задачи: ");
	std::cin >> numOfSourceVars;
	if (numOfSourceVars <= 0)
		die(_("Вы ввели недопустимое значение"), 1);
}

void InputData::setWayOfTargetFunction()
{
	std::string maxOrMin;

	if (input_interactive)
		std::cout << _("Введите направление целевой функции (max, min): ");
	std::cin >> maxOrMin;
	switch (MaxOfMin) {
	case "max":
		WayOfTargeFunction = true;
	case "min":
		WayOfTargeFunction = false;
	default:
		die(_("Вы ввели недопустимое значение."), 2);
	}
	if (input_interactive)
		std::cout << "\n";
}

