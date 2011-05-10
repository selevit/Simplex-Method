#include <iostream>

#include <string>

#include "Simplex.h"

void Simplex::setValues()
{
	int numOfIteration = 0;
	
	do
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
		Simplex::displayTable(numOfIteration);
	}
	while(!checkPlane());
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

void Simplex::displayTable (int numOfIteration)
{
	int i, j;
	
	std::cout << std::endl << std::endl;
	std::cout << numOfIteration << "-й план:" << std::endl << std::endl;
	for (i = 0; i < numOfSourceVars; ++i)
	{
		std::cout << "X" << basisVars [0][i] << "		";
		std::cout <<  basisVars[1][i] << "		";
		for (j = 0; j < numOfSourceVars * 2; ++j)
		{
			std::cout << varsFactors [i][j] << "	";			
		}
		if (!checkPlane())
			std::cout << "	" <<  thColumn [i];
		std::cout << std::endl << std::endl;
	}
	std::cout << "F(X)		";
	std::cout << targetFunction << "		";
	for (i = 0; i < numOfSourceVars * 2; ++i)
	{
		std::cout << indexString [i] << "	";
	}
	std::cout << std::endl << std::endl;
	if (!checkPlane())
		std::cout << "Данный план не оптимален, его необходимо улучшить." << std::endl;
	else
		std::cout << "Данный план является оптимальным. Решение найдено." << std::endl;
	std::cout << std::endl;
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
	
	if (numOfIteration == 1)
	{
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
	}
	else
	{
		double * tmpBasisVars = new double [numOfSourceVars];
		double A = basisVars[1][indexOfLeavingRow];
		double B;
		for (i = 0; i < numOfSourceVars; ++i)
		{
			B = varsFactors [i][indexOfLeavingColumn];
			tmpBasisVars [i] = basisVars [1][i];
			tmpBasisVars [i] = i == indexOfLeavingRow ? tmpBasisVars[i] / allowingMember :  basisVars [1][i] - ((A * B) / allowingMember);
		}
		for (int i = 0; i < numOfSourceVars; ++i)
		{
			basisVars[1][i] = tmpBasisVars[i];
		}
		basisVars[0][indexOfLeavingRow] = indexOfLeavingColumn + 1;
	}
}	

void Simplex::setFactorsOfVars(int numOfIteration)
{
	int i, j;
	
	if (numOfIteration == 1)
	{
		varsFactors = new double * [numOfSourceVars];
			for (i = 0; i < numOfSourceVars; ++i)
				varsFactors[i] = new double [numOfSourceVars * 2];
			
		for  (i = 0; i < numOfSourceVars; ++i)
		{
			for(j = 0; j < numOfSourceVars * 2; ++j)

				if (j < numOfSourceVars)
					varsFactors[i][j] = factorsOfSystemVars[i][j];
				else
					varsFactors [i][j] = i + numOfSourceVars == j;
		
		}
	}
	else
	{
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
				double A = varsFactors [indexOfLeavingRow][j];
				double B = varsFactors [i][indexOfLeavingColumn];
				tmpVarsFactors[i][j] = i == indexOfLeavingRow ? tmpVarsFactors [i][j] / allowingMember :  varsFactors[i][j] - ((A * B) / allowingMember);
			}
		}
		
		varsFactors = tmpVarsFactors;
	}
}


void Simplex::setIndexString (int numOfIteration)
{
	int i;
	
	if (numOfIteration == 1)
	{
		indexString = new double [numOfSourceVars * 2];
		for (i = 0; i < numOfSourceVars * 2; ++i)
			indexString [i] = ((i < numOfSourceVars) ? -(factorsOfTargetFunctionVars [i]) : 0);
	}
	else
	{
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
}

void Simplex::setTargetFunction(int numOfIteration)
{
	if (numOfIteration == 1)
		targetFunction = 0;
	else
	{
		double A = basisVars [1][indexOfLeavingRow];
		double B = indexString [indexOfLeavingColumn];
		targetFunction -= ((A * B) / allowingMember);
		
	}
}

void Simplex::setThColumn ()
{
	int i;

	thColumn = new double [numOfSourceVars];

	for (i = 0; i < numOfSourceVars; ++i)
	{
		thColumn [i] = basisVars [1][i] / varsFactors [i][indexOfLeavingColumn];
	}
}
