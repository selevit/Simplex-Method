#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "Simplex.h"

void Simplex::init() {
	int i,j;	
	old_plane = new Plane(numOfSourceVars);
	new_plane = new Plane(numOfSourceVars);

	for (i = 0; i < numOfSourceVars; ++i) {
		(*new_plane->basisVars)[0][i] = numOfSourceVars + i + 1;
		(*new_plane->basisVars)[1][i] = freeMembersOfSystem[i];
	}

	for (i = 0; i <numOfSourceVars; i++)
		new_plane->indexString[i] = -factorsOfTargetFunctionVars[i];

	for (; i < numOfSourceVars * 2; i++)
		new_plane->indexString[i] = 0;

	for (i = 0; i < numOfSourceVars; ++i) {
		for (j = 0; j < numOfSourceVars; j++) {
			(*new_plane->varsFactors)[i][j] = factorsOfSystemVars[i][j];
		 	if (freeMembersOfSystem[i] < 0)
				(*new_plane->varsFactors)[i][j] *= -1;
		}
		for (; j < numOfSourceVars*2; j++)
			(*new_plane->varsFactors)[i][j] = i + numOfSourceVars == j;
	}
	
	setIndexOfLeavingColumn(new_plane);
	
	for (i = 0; i < numOfSourceVars; ++i)
		new_plane->thColumn[i] = (*new_plane->basisVars)[1][i] / (*new_plane->varsFactors)[i][new_plane->indexOfLeavingColumn];
	
	setIndexOfLeavingRow(new_plane);
	setAllowingMember(new_plane);
}

void Simplex::setValues() {

	int i = 1;
	Plane* t;
	enum result r;

	for (;;) {
		if (good_solution == (r = checkPlane(new_plane))) {
			dumpToTableTxt(new_plane, i, r);
			displayResult(new_plane, i, r);
			break;
		} else {
			if(!checkThColumn(new_plane)) {
				r = no_solution;
				dumpToTableTxt(new_plane, i, r);
				displayResult(new_plane, i, r);
				break;
			}
			dumpToTableTxt(new_plane, i, r);
		}

		++i;
		t = old_plane; old_plane = new_plane; new_plane = t;

		setTargetFunction(old_plane, new_plane);
		setBasisVars(old_plane, new_plane);
		setIndexString(old_plane, new_plane);
		setFactorsOfVars(old_plane, new_plane);
		setIndexOfLeavingColumn(new_plane);
		setThColumn(new_plane);
		setIndexOfLeavingRow(new_plane);
		setAllowingMember(new_plane);
	}	
}

bool Simplex::checkThColumn(Plane* p) {
	for (int i = 0; i < numOfSourceVars; ++i)
		if (p->thColumn[i] < 0)
			return false;
	return true;
}

enum result Simplex::checkPlane(Plane* p) {
	int i;
	
	for (i = 0; i < numOfSourceVars; ++i) {
		if (wayOfTargetFunction) {
			if (p->indexString[i] < 0) return bad_solution;
		} else {
			if (p->indexString[i] >= 0) return bad_solution;
		}
	}
	return good_solution;
}

void Simplex::displayResult(Plane* p, unsigned int iteration, enum result r) {
	int i;

	std::stringstream out; out << "\n\n";

	switch(r) {
	case good_solution:
		out << "Оптимальный план найден. Количество итераций = " << iteration;
		break;
	case no_solution:
		std::cout << out.str() << "Целевая функция не ограничена. Задача с данным условием не имеет решений.\n" << std::flush;
		return;
	default:
		break;
	}
	out << "\n\n";
	for (i = 0; i < numOfSourceVars; i++)
		out << "x" << (*p->basisVars)[0][i] << " = " << (*p->basisVars)[1][i] << "\n";

	out << "\n\nf(x) = " << p->targetFunction << "\n";

	std::cout << out.str() << std::flush;
}

void Simplex::dumpToTableTxt(Plane* p, unsigned int iteration, enum result r) {
	int i, j;
	static std::ofstream file("table.txt");
	std::stringstream buf;

	buf << "Задана целевая функция: f(x) = ";	
	for (i = 0; i < numOfSourceVars; ++i) {
		if (factorsOfTargetFunctionVars[i] > 0 && i)
			buf << " + ";
		buf << factorsOfTargetFunctionVars[i] << "x" <<  i + 1;
	}

	buf << "\n\n";
	buf << iteration << "-й план \n\n";

	for (i = 0; i < numOfSourceVars; ++i) {
		buf << "x" << std::setw(3) << std::left << (*p->basisVars)[0][i] << "\t";
		buf << std::setw(5) << (*p->basisVars)[1][i] << "\t";
		for (j = 0; j < numOfSourceVars * 2; ++j)
			buf << std::setw(7) << (*p->varsFactors)[i][j] << "	";
		if (r == bad_solution)
			buf <<  p->thColumn [i];
		buf << "\n\n";
	}

	buf << "f(x)\t" << std::setw(5) << p->targetFunction << "\t";
	
	for (i = 0; i < numOfSourceVars * 2; ++i)
		buf << std::setw(7) << p->indexString[i] << "\t";
	
	buf << "\n\n";

	switch(r) {
	case bad_solution:
		buf << "Данный план не оптимален, его необходимо улучшить.";
		break;
	case good_solution:
		buf << "Данный план является оптимальным. Решение найдено.";
		break;
	case no_solution:
		buf << "Целевая функция не ограничена, данная задача не имеет решения.";
		break;
	}

	buf << "\n\n\n";

	file << buf.str() << std::flush;
}

void Simplex::setIndexOfLeavingColumn(Plane* p) { 
	int i;
	double minOfIndexString = p->indexString[0];
	p->indexOfLeavingColumn = 0;

	for (i = 0; i < numOfSourceVars * 2; ++i) {
		if (p->indexString[i] < 0 && minOfIndexString > p->indexString[i]) {
			minOfIndexString = p->indexString[i];
			p->indexOfLeavingColumn = i;
		}
	}
}

void Simplex::setIndexOfLeavingRow(Plane* p) {
	int i;
	double minOfThColumn = p->thColumn[0];
	p->indexOfLeavingRow = 0;

	for (i = 0; i < numOfSourceVars; ++i) {
		if (minOfThColumn > p->thColumn[i]) {
			minOfThColumn = p->thColumn[i];
			p->indexOfLeavingRow = i;
		}
	}
}

void Simplex::setAllowingMember(Plane* p) {
	p->allowingMember = (*p->varsFactors)[p->indexOfLeavingRow][p->indexOfLeavingColumn];
}

void Simplex::setBasisVars(Plane* source, Plane* target) {
		int i;
		double A = (*source->basisVars)[1][source->indexOfLeavingRow];
		double B;

		for (i = 0; i < numOfSourceVars; ++i) {
			if (i == source->indexOfLeavingRow) {
				(*target->basisVars)[0][source->indexOfLeavingRow] = source->indexOfLeavingColumn + 1;
				(*target->basisVars)[1][i] = (*source->basisVars)[1][i] / source->allowingMember;
			} else {
				(*target->basisVars)[0][i] = (*source->basisVars)[0][i];
				B = (*source->varsFactors)[i][source->indexOfLeavingColumn];
				(*target->basisVars)[1][i] = (*source->basisVars)[1][i] - ((A * B) / source->allowingMember);
			}
		}
}

void Simplex::setFactorsOfVars(Plane* source, Plane* target) {
	int i, j;
	double A, B;

	for (i = 0; i < numOfSourceVars; ++i) {
		for (j = 0; j < numOfSourceVars * 2; ++j) {
			if (i == source->indexOfLeavingRow) {
				(*target->varsFactors)[i][j] = (*source->varsFactors)[i][j] / source->allowingMember;
			} else {
				A = (*source->varsFactors)[source->indexOfLeavingRow][j];
				B = (*source->varsFactors)[i][source->indexOfLeavingColumn];
				(*target->varsFactors)[i][j] = (*source->varsFactors)[i][j] - ((A * B) / source->allowingMember);
			}
		}
	}
}

void Simplex::setIndexString(Plane* source, Plane* target) {
		int i;
		double A, B;

		for (i = 0; i < numOfSourceVars * 2; ++i) {
			A = (*source->varsFactors)[source->indexOfLeavingRow][i];
			B = source->indexString[source->indexOfLeavingColumn];
			target->indexString[i] = source->indexString[i] - ((A * B) / source->allowingMember);
		}
}

void Simplex::setTargetFunction(Plane* source, Plane* target) {
		double A = (*source->basisVars)[1][source->indexOfLeavingRow];
		double B = source->indexString[source->indexOfLeavingColumn];
		target->targetFunction = source->targetFunction - ((A * B) / source->allowingMember);
}

void Simplex::setThColumn (Plane* p) {
	for (int i = 0; i < numOfSourceVars; ++i)
		p->thColumn[i] = (*p->basisVars)[1][i] / (*p->varsFactors)[i][p->indexOfLeavingColumn];
}
