#include <iostream>

#include <fstream>

#include <string>

#include <sstream>

#include <algorithm>

#include "Simplex.h"



void Simplex::init()
{
	int i,j;	

	currentPlane = new Plane<double>(numOfSourceVars);
	bestPlane = new Plane<double>(numOfSourceVars);
	tmp = new SubPlane<double>(numOfSourceVars);

	for (i = 0; i < numOfSourceVars; ++i)
	{
		(*currentPlane->basisVars)[0][i] = numOfSourceVars + i + 1;
		(*currentPlane->basisVars)[1][i] = freeMembersOfSystem[i];
	}
	
	for (i = 0; i < numOfSourceVars * 2; ++i)
			currentPlane->indexString[i] = ((i < numOfSourceVars) ? -(factorsOfTargetFunctionVars [i]) : 0);

	for  (i = 0; i < numOfSourceVars; ++i)
	{
		for(j = 0; j < numOfSourceVars * 2; ++j)
		{
			if (j < numOfSourceVars)
				(*currentPlane->varsFactors)[i][j] = freeMembersOfSystem [i] < 0 ? factorsOfSystemVars [i][j] * -1 : factorsOfSystemVars[i][j];
			else
				(*currentPlane->varsFactors)[i][j] = i + numOfSourceVars == j;
		}
	}
	
	setIndexOfLeavingColumn();
	
	for (i = 0; i < numOfSourceVars; ++i)
		currentPlane->thColumn[i] = (*currentPlane->basisVars)[1][i] / (*currentPlane->varsFactors)[i][currentPlane->indexOfLeavingColumn];
	
	setIndexOfLeavingRow();
	
	setAllowingMember();
}


int Simplex::setValues()
{

	int i;
	int numOfIteration = 1;
	printOutData(numOfIteration);

	while (!checkPlane() && checkThColumn()) 
	{
		
		++numOfIteration;
		setTargetFunction(numOfIteration);
		setBasisVars(numOfIteration);
		setIndexString(numOfIteration);
		setFactorsOfVars(numOfIteration);
		setIndexOfLeavingColumn();
		setThColumn();
		setIndexOfLeavingRow();
		setAllowingMember();
//		if (checkPlane() || !checkThColumn())
//		{
			printOutData(numOfIteration);
//		}
	
	}	
	

	displayResult(numOfIteration);

	return 0;
}

bool Simplex::checkThColumn()
{
	int i;
	bool result = true;

	for (i = 0; i < numOfSourceVars; ++i)
	{
		if (currentPlane->thColumn [i] <= 0)
		{
			result = false;
			break;
		}
	}

	return result;

}

bool Simplex::checkPlane()
{
	int i;
	bool result = true; 
	
	for (i = 0; i < numOfSourceVars; ++i)
	{
		if (wayOfTargetFunction)

			if (currentPlane->indexString[i] < 0)
			{
				result = false;
				break;
			}
//			else
//			{
//				bestPlane = currentPlane;
//			}
		
		else if (!wayOfTargetFunction)
		
			if (currentPlane->indexString[i] >= 0)
			{
				result = false;
				break;
			}
//			else
//			{
//				bestPlane = currentPlane;
//			}
	}
	return result;
}

void Simplex::displayResult (int numOfIteration)
{
	int i, j;
	std::cout << std::endl << std::endl;
	if (checkPlane() && checkThColumn())
		std::cout << "Оптимальный план найден. Количество итераций = " << numOfIteration << std::endl << std::endl;
	else if (!checkPlane() && checkThColumn())
		std::cout << "Данная задача имеет одно единственное решение, но оно не является оптимальным.\nЭтим решением является первый опорный план задачи." << std::endl << std::endl;
	else
		std::cout << "Целевая функция не ограничена. Задача с данным условием не имеет решений." << std::endl << std::endl;	
	for (i = 0; i < numOfSourceVars; ++i)
		std::cout << "X" << (*currentPlane->basisVars)[0][i] << " = " <<  (*currentPlane->basisVars)[1][i] << std::endl;	
	std::cout << std::endl;
	std::cout << "F(X) = " << currentPlane->targetFunction << std::endl << std::endl;
}

void Simplex::printOutData(int numOfIteration)
{

	int i, j;

	std::stringstream printResult;

	std::stringstream outVar;
	
	for (i = 0; i < numOfSourceVars; ++i)
	{
			if (factorsOfTargetFunctionVars[i] > 0)
				if (i)
					outVar << " + " << factorsOfTargetFunctionVars[i] << "X" <<  i + 1;
				else
					outVar << factorsOfTargetFunctionVars[i] << "X" <<  i + 1;
					
			else if (factorsOfTargetFunctionVars < 0)
				outVar << factorsOfTargetFunctionVars[i]  <<  "X" << i + 1;

	}
	printResult << "Задана целевая функция: F(X) = " << outVar.str();

	printResult << std::endl << std::endl;
	printResult <<  numOfIteration << "-й план " << std::endl << std::endl;
	

	for (i = 0; i < numOfSourceVars; ++i)
	{
		printResult << "X" << (*currentPlane->basisVars)[0][i] << "		";
		printResult <<  (*currentPlane->basisVars)[1][i] << "		";
		for (j = 0; j < numOfSourceVars * 2; ++j)
		{
			printResult << (*currentPlane->varsFactors)[i][j] << "	";			
		}
		if (!checkPlane())
			printResult << "	" <<  currentPlane->thColumn [i];
		printResult << std::endl << std::endl;
	}

	printResult << "F(X)		";

	printResult << currentPlane->targetFunction << "		";
	
	for (i = 0; i < numOfSourceVars * 2; ++i)
	{
		printResult << currentPlane->indexString [i] << "	";
	}
	printResult << std::endl << std::endl;

	if (!checkPlane())
		printResult << "Данный план не оптимален, его необходимо улучшить." << std::endl << std::endl;

	else
		printResult << "Данный план является оптимальным. Решение найдено." << std::endl << std::endl;

	printResult << std::endl;

	std::ofstream outFile ("TABLE.TXT", std::ios::app);

	outFile << printResult.str();
}

void Simplex::setIndexOfLeavingColumn()
{
	int i, j;
	double minOfIndexString = currentPlane->indexString[0];
	int indexOfMin = 0;
	for (i = 0; i < numOfSourceVars * 2; ++i)
	{

		if (currentPlane->indexString[i] < 0 && minOfIndexString > currentPlane->indexString[i])
		{
			minOfIndexString = currentPlane->indexString [i];
			indexOfMin = i;
		}

	}
	currentPlane->indexOfLeavingColumn = indexOfMin;
}

void Simplex::setIndexOfLeavingRow()
{
	int i;
	double minOfThColumn = currentPlane->thColumn [0];
	int indexOfMin = 0;
	for (i = 0; i < numOfSourceVars; ++i)
	{
		if (minOfThColumn > currentPlane->thColumn [i])
		{
			minOfThColumn = currentPlane->thColumn [i];
			indexOfMin = i;
		}
	}
	currentPlane->indexOfLeavingRow = indexOfMin;
}

void Simplex::setAllowingMember()
{
	currentPlane->allowingMember = (*currentPlane->varsFactors)[currentPlane->indexOfLeavingRow][currentPlane->indexOfLeavingColumn];
}

void Simplex::setBasisVars(int numOfIteration)
{
		int i;

		double A = (*currentPlane->basisVars)[1][currentPlane->indexOfLeavingRow];
		double B;
		for (i = 0; i < numOfSourceVars; ++i)
		{
			B = (*currentPlane->varsFactors)[i][currentPlane->indexOfLeavingColumn];
			(*tmp->basisVars)[1][i] = (*currentPlane->basisVars)[1][i];
			if (i == currentPlane->indexOfLeavingRow) {
				(*tmp->basisVars)[1][i] /= currentPlane->allowingMember;
			} else {
				(*tmp->basisVars)[1][i] = (*currentPlane->basisVars)[1][i] - ((A * B) / currentPlane->allowingMember);
			}
		}

		memcpy((*currentPlane->basisVars)[1], (*tmp->basisVars)[1], numOfSourceVars*sizeof(double));

		(*currentPlane->basisVars)[0][currentPlane->indexOfLeavingRow] = currentPlane->indexOfLeavingColumn + 1;
}	

void Simplex::setFactorsOfVars(int numOfIteration)
{
		int i, j;
		double A, B;
	
		for (i = 0; i < numOfSourceVars; ++i)
		{
			for (j = 0; j < numOfSourceVars * 2; ++j)
			{ 
				(*tmp->varsFactors)[i][j] = (*currentPlane->varsFactors)[i][j];
				A = (*currentPlane->varsFactors)[currentPlane->indexOfLeavingRow][j];
				B = (*currentPlane->varsFactors)[i][currentPlane->indexOfLeavingColumn];
				if (i == currentPlane->indexOfLeavingRow) {
					(*tmp->varsFactors)[i][j] /= currentPlane->allowingMember;
				} else {
					(*tmp->varsFactors)[i][j] = (*currentPlane->varsFactors)[i][j] - ((A * B) / currentPlane->allowingMember);
				}

			}
		}
		(*currentPlane->varsFactors) = (*tmp->varsFactors);
}


void Simplex::setIndexString (int numOfIteration)
{
		int i;
		double A, B;
		for (i = 0; i < numOfSourceVars * 2; ++i)
		{
			A = (*currentPlane->varsFactors)[currentPlane->indexOfLeavingRow][i];
			B = currentPlane->indexString [currentPlane->indexOfLeavingColumn];
			tmp->indexString [i] = currentPlane->indexString [i];
			tmp->indexString [i] = currentPlane->indexString [i] - ((A * B) / currentPlane->allowingMember);
		}
		
		memcpy(currentPlane->indexString, tmp->indexString, numOfSourceVars*2*sizeof(double));
}

void Simplex::setTargetFunction(int numOfIteration)
{
		double A = (*currentPlane->basisVars)[1][currentPlane->indexOfLeavingRow];
		double B = currentPlane->indexString[currentPlane->indexOfLeavingColumn];
		currentPlane->targetFunction -= ((A * B) / currentPlane->allowingMember);
}

void Simplex::setThColumn ()
{
	int i;
	for (i = 0; i < numOfSourceVars; ++i)
		currentPlane->thColumn [i] = (*currentPlane->basisVars)[1][i] / (*currentPlane->varsFactors)[i][currentPlane->indexOfLeavingColumn];
}
