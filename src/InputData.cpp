#include <iostream>
#include <fstream>
#include <string>
#include "InputData.h"

void InputData::getAndSetInputData() {
	setInputFile();
	setNumOfSourceVars();
	setFactorsOfTargetFunctionVars();
	setWayOfTargetFunction();
	setFactorsOfSystemVars();
	setFreeMembersOfSystem();
}

void InputData::selectInputMethod() {
	int userInputMethod;
	std::cout << "Выберите метод ввода (вручную - 1, из файла - 2): ";
	std::cin >> userInputMethod;
	
	switch (userInputMethod) {
		case 1:
			inputMethod = false;
			std::cout << std::endl;
			break;
		case 2:
			inputMethod = true;
			std::cout << std::endl;
			break;
		default:
			error(1);
			selectInputMethod();
			break;
	}
}

void InputData::setInputFile () {
	inputFileName = new char;
	char * tmpInputFileName = new char;
	if (inputMethod) {	
		std::cout << "Введите имя или путь к входному файлу: ";
		std::cin >> tmpInputFileName;
		std::ofstream check (tmpInputFileName, std::ios_base::in);
		if (!check) {
			error(2);
			setInputFile();
		}
		else
			inputFileName = tmpInputFileName;
	}
		
}

double * InputData::getFreeMembersOfSystem() {
	double * freeMembers = new double [numOfSourceVars];
	for (int i = 0; i < numOfSourceVars; ++i) {
		std::cout << "Введите значение свободного члена для " << i + 1 << "-го неравенства: ";
		std::cin >> freeMembers [i];
	}
	std::cout << std::endl;
	return freeMembers;
}

void InputData::setFreeMembersOfSystem () {
	freeMembersOfSystem = getFreeMembersOfSystem();
}

double ** InputData::getFactorsOfSystemVars() {
	double ** factorsOfSystemVariables = new double * [numOfSourceVars];

	for (int i = 0; i < numOfSourceVars; ++i)
		factorsOfSystemVariables [i] = new double [numOfSourceVars];

	for (int i = 0; i < numOfSourceVars; ++i) {
		for (int j = 0; j < numOfSourceVars; ++j) {
			std::cout << "Введите коэффициент при X" << j + 1 << " для " << i + 1 << "-го неравенстве: ";
			std::cin >> factorsOfSystemVariables [i][j];
		}
		std::cout << std::endl;
	}
	return factorsOfSystemVariables;
}

void InputData::setFactorsOfSystemVars() {
	factorsOfSystemVars = getFactorsOfSystemVars();	
}

double * InputData::getFactorsOfTargetFunctionVars() {
	double * factorsOfTargetFunctionVariables  = new double [numOfSourceVars];
	std::cout << std::endl;

	for (int i = 0; i < numOfSourceVars; ++i) {
		std::cout << "Введите коэфициент целевой функции при X" << i + 1 << ": ";
		std::cin >> factorsOfTargetFunctionVariables [i];
	}
	std::cout << std::endl;
	return  factorsOfTargetFunctionVariables;
}

void InputData::setFactorsOfTargetFunctionVars() {
	factorsOfTargetFunctionVars =  getFactorsOfTargetFunctionVars();
}

int InputData::getNumOfSourceVars() {
	int result;
	std::cout << "Введите количество основных переменных задачи: ";
	std::cin >> result;
	return result;
}

bool InputData::setNumOfSourceVars() {
	int result = getNumOfSourceVars();
	if (result > 0) {
		numOfSourceVars = result;
		return true;
	} else {
		error(1);
		setNumOfSourceVars();
	}
}

bool InputData::getWayOfTargetFunction() {
	std::string maxOrMin;
	std::cout << "Введите направление целевой функции (max, min): ";
	std::cin >> maxOrMin;
	if (maxOrMin == "max") {
		std::cout << std::endl;
		return true;
	} else if (maxOrMin == "min") {
		std::cout << std::endl;
		return false;
	} else {
		error(1);
		getWayOfTargetFunction();
	}
}
void InputData::setWayOfTargetFunction() {
	wayOfTargetFunction = getWayOfTargetFunction();
}

void InputData::error(int numberOfError) {
	std::string errorMessage;

	switch (numberOfError) {
		case 0:
			errorMessage = "Возникла непредвиненная ошибка. попробуйте еще раз."; 
			break;
		case 1:
			errorMessage = "Вы ввели недопустимое значение.";
			break;
		case 2: errorMessage = "Нет доступа к файлу!";
			break;
		case 4: errorMessage = "Целевая функция не ограничена. Задача с данным условием не имеет решений.";
			break;
	}

	std::cout << std::endl;
	std::cout << errorMessage;
	std::cout << std::endl << std::endl;;
}
