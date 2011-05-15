#include <iostream>

#include <fstream>

#include <string>

#include <sstream>

#include <algorithm>

#include "Simplex.h"



bool Simplex::init()
{
	int i,j;	
	
	
	targetFunction = 0;

	basisVars = new double * [2];

	for (i = 0; i < 2; ++i)
	{
		basisVars [i] = new double [numOfSourceVars];
	}

	for (i = 0; i < numOfSourceVars; ++i)
	{
		basisVars[0][i] = numOfSourceVars + i + 1;
		basisVars[1][i] = freeMembersOfSystem[i];
	}
	
	
	indexString = new double [numOfSourceVars * 2];
		for (i = 0; i < numOfSourceVars * 2; ++i)
			indexString [i] = ((i < numOfSourceVars) ? -(factorsOfTargetFunctionVars [i]) : 0);


	varsFactors = new double * [numOfSourceVars];
		for (i = 0; i < numOfSourceVars; ++i)
			varsFactors[i] = new double [numOfSourceVars * 2];
		
	for  (i = 0; i < numOfSourceVars; ++i)
	{
		for(j = 0; j < numOfSourceVars * 2; ++j)
		{
			if (j < numOfSourceVars)
				varsFactors[i][j] = freeMembersOfSystem [i] < 0 ? factorsOfSystemVars [i][j] * -1 : factorsOfSystemVars[i][j];
			else
				varsFactors [i][j] = i + numOfSourceVars == j;
		}
	}
	
	
	setIndexOfLeavingColumn();
	
	
	thColumn = new double [numOfSourceVars];
	
	for (i = 0; i < numOfSourceVars; ++i)
		thColumn [i] = basisVars [1][i] / varsFactors [i][indexOfLeavingColumn];
	
	
	setIndexOfLeavingRow();
	
	
	
	setAllowingMember();
}


int Simplex::setValues()
{

	int i;
	int numOfIteration = 1;
	Simplex::printOutData(numOfIteration);

	while (!checkPlane() && checkThColumn()) 
	{
		
		++numOfIteration;
		Simplex::setTargetFunction(numOfIteration);
		Simplex::setBasisVars(numOfIteration);
		Simplex::setIndexString(numOfIteration);
		Simplex::setFactorsOfVars(numOfIteration);
		Simplex::setIndexOfLeavingColumn();
		Simplex::setThColumn();
		Simplex::setIndexOfLeavingRow();
		Simplex::setAllowingMember();
		Simplex::printOutData(numOfIteration);	
	
	}

	Simplex::displayResult(numOfIteration);

	return 0;
}

bool Simplex::checkThColumn()
{
	int i;
	bool result = true;

	for (i = 0; i < numOfSourceVars; ++i)
	{
		if (thColumn [i] <= 0)
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

			if (indexString[i] < 0)
			{
				result = false;
				break;
			}
		
		else
		
			if (indexString[i] < 0)
			{
				result = false;
				break;
			}
	}
	return result;
}

void Simplex::displayResult (int numOfIteration)
{
	int i, j;
	if (checkPlane() && checkThColumn())
	{
		std::cout << std::endl << std::endl;
		std::cout << "Оптимальный план найден. Количество итераций = " << numOfIteration << std::endl << std::endl;
		for (i = 0; i < numOfSourceVars; ++i)
			std::cout << "X" << basisVars [0][i] << " = " <<  basisVars[1][i] << std::endl;	
		std::cout << std::endl;
		std::cout << "F(X) = " << targetFunction << std::endl << std::endl;
	}
	else
		error(4);
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
		printResult << "X" << basisVars [0][i] << "		";
		printResult <<  basisVars[1][i] << "		";
		for (j = 0; j < numOfSourceVars * 2; ++j)
		{
			printResult << varsFactors [i][j] << "	";			
		}
		if (!checkPlane())
			printResult << "	" <<  thColumn [i];
		printResult << std::endl << std::endl;
	}

	printResult << "F(X)		";

	printResult << targetFunction << "		";
	
	for (i = 0; i < numOfSourceVars * 2; ++i)
	{
		printResult << indexString [i] << "	";
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
	double minOfIndexString = indexString[0];
	int indexOfMin = 0;
	for (i = 0; i < numOfSourceVars * 2; ++i)
	{

		if (indexString[i] < 0 && minOfIndexString > indexString[i])
		{
			minOfIndexString = indexString [i];
			indexOfMin = i;
		}

	}
	indexOfLeavingColumn = indexOfMin;
}

void Simplex::setIndexOfLeavingRow()
{
	int i;
	double minOfThColumn = thColumn [0];
	int indexOfMin = 0;
	for (i = 0; i < numOfSourceVars; ++i)
	{
		if (minOfThColumn > thColumn [i])
		{
			minOfThColumn = thColumn [i];
			indexOfMin = i;
		}
	}
	indexOfLeavingRow = indexOfMin;
}

void Simplex::setAllowingMember()
{
	allowingMember = varsFactors [indexOfLeavingRow][indexOfLeavingColumn];
}

void Simplex::setBasisVars(int numOfIteration)
{
		int i;
		double * tmpBasisVars = new double [numOfSourceVars];
		double A = basisVars[1][indexOfLeavingRow];
		double B;
		for (i = 0; i < numOfSourceVars; ++i)
		{
			B = varsFactors [i][indexOfLeavingColumn];
			tmpBasisVars [i] = basisVars [1][i];
			tmpBasisVars [i] = i == indexOfLeavingRow ? tmpBasisVars[i] / allowingMember :  basisVars [1][i] - ((A * B) / allowingMember);
		}
		for (i = 0; i < numOfSourceVars; ++i)
		{
			basisVars[1][i] = tmpBasisVars[i];
		}
		basisVars[0][indexOfLeavingRow] = indexOfLeavingColumn + 1;
}	

void Simplex::setFactorsOfVars(int numOfIteration)
{
		int i, j;
		
		double ** tmpVarsFactors = new double * [numOfSourceVars];

		for (i = 0; i < numOfSourceVars; ++i)
		{
			tmpVarsFactors [i] = new double [numOfSourceVars * 2];
		}

		double A, B;
		
		for (i = 0; i < numOfSourceVars; ++i)
		{
			for (j = 0; j < numOfSourceVars * 2; ++j)
			{
				tmpVarsFactors [i][j] = varsFactors [i][j];
				A = varsFactors [indexOfLeavingRow][j];
				B = varsFactors [i][indexOfLeavingColumn];
				tmpVarsFactors[i][j] = i == indexOfLeavingRow ? tmpVarsFactors [i][j] / allowingMember :  varsFactors[i][j] - ((A * B) / allowingMember);
			}
		}
		varsFactors = tmpVarsFactors;
}


void Simplex::setIndexString (int numOfIteration)
{
		int i;
		double * tmpIndexString = new double [numOfSourceVars * 2];
		double A, B;
		for (i = 0; i < numOfSourceVars * 2; ++i)
		{
			A = varsFactors [indexOfLeavingRow][i];
			B = indexString [indexOfLeavingColumn];
			tmpIndexString [i] = indexString [i];
			tmpIndexString [i] = indexString [i] - ((A * B) / allowingMember);
		}
		
		indexString = tmpIndexString;
}

void Simplex::setTargetFunction(int numOfIteration)
{
		double A = basisVars [1][indexOfLeavingRow];
		double B = indexString [indexOfLeavingColumn];
		targetFunction -= ((A * B) / allowingMember);
}

bool Simplex::setThColumn ()
{
	int i;
	for (i = 0; i < numOfSourceVars; ++i)
		thColumn [i] = basisVars [1][i] / varsFactors [i][indexOfLeavingColumn];
}
