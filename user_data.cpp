#include <iostream>
#include <string>
#include <cstdlib>

#include "user_data.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void error(int err_no)
{
	switch(err_no) {
		case 0:
			cout << "\nВы ввели некорректное значение.\n" << endl;
			break;
		case 1:
			cout << "\nВы не можете задать менее двух ограничений.\n" << endl;
			break;
		case 2:
			cout << "\nВы не можете задать больше 500 ограничений.\n" << endl;
			break;
		case 3:
			cout << "\nВы не можете задать менее двух переменных.\n" << endl;
			break;
		case 4:
			cout << "\nВы не можете задать более 500 уравнений.\n" << endl;
			break;
	}
}

void user_data::get_data_from_user()
{
	string num_limits, num_vars, s_var, fr_m, sn, func, w;
	int i, j;
	bool validator = false;
	

	do {
		cout << "Введите количество ограничений в системе: ";
		getline(cin, num_limits);
		if (atoi(num_limits.c_str()) < 2)
			error(1);
		else if (atoi(num_limits.c_str()) > 500)
			error(2);
		else
			validator = true;
			
	} while (!validator);

	num_l = atoi(num_limits.c_str());
	validator = false;

	do {
		cout << "Введите количество переменных в системе ограничений: ";
		getline(cin, num_vars);
	if (atoi(num_vars.c_str()) < 2) 
		error(3);
	else if (atoi (num_vars.c_str()) > 500)
		error(4);
	else
		validator = true;
	} while (!validator);

	num_v = atoi(num_vars.c_str());
	validator = false;
	
	function = new double [num_v];
	system = new double *[num_l];
	for (i = 0; i < num_l; i++)
		system[i] = new double [num_v];
	fm = new double [num_l];
	sign = new int [num_l];

	cout << "\nЗаполните коэффициенты при целевой функции.\n" << endl;

	for (i = 0; i < num_v; i++) {
		do {
			cout << "Введите коэффициент целевой фукнции при x" << i + 1 << ": ";
			getline(cin, func);
			if (atof(func.c_str()) == 0)
				error(0);
			else {
				validator = true;
				function[i] = atof(func.c_str());
			}
		} while (!validator);
		validator = false;
	}
	
	do {
		cout << "Введите направление целевой функции ( min, max ) : ";
		getline(cin, w);
		if (w == "max" || w == "MAX" || w == "min" || w == "MIN") {
			validator = true;
			if (w == "max" || w == "MAX")
				way = true;
			else
				way = false;
		}
		else
			error (0);

	} while (!validator);
	cout << "\nЗаполните систему ограничений.\n" << endl;

	for (i = 0; i < num_l; i++) {
		cout << "Заполните " << i + 1 << "-е ограничение.\n" << endl;
		for (j = 0; j < num_v; j++) {
			do {
				cout << "Введите коэффициэнт при x" << j + 1 << ": ";
				getline(cin, s_var);
				if (atof(s_var.c_str()) == 0)
					error (0);
				else {
					validator = true;
				}
			} while (!validator);
			system[i][j] = atof(s_var.c_str());
			validator = false;
		}

		do {
			cout << "Введите знак при " << i + 1 << "-м ограничении ( <=, =, >= ) : ";
			getline(cin, sn);
			if (sn == "<=" || sn == "=" || sn == ">=") {
				validator = true;
				if (sn == "<=")
					sign[i] = 0;
				if (sn == "=")
					sign[i] = 1;
				if (sn == ">=")	
					sign[i] = 2;
				}
			else
				error(0);
			cout << sign[i] << endl;
		} while (!validator);

		validator = false;

		do {
			cout << "Введите свободный член при " << i + 1 << "-м ограничении: ";
			getline(cin, fr_m);
			if (atof(fr_m.c_str()) == 0)
				error(0);
			else
				validator = true;
		} while (!validator);

		fm[i] = atof(fr_m.c_str());
		validator = false;

		cout << endl;
	}
	
}
