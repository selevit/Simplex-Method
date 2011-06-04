#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

#include "user_data.h"
#include "simplex.h"

using std::cout;
using std::endl;

void simplex::init()
{
	int i, j;
	func = 0;
	sv = new double *[num_l];
	for (i = 0; i < num_l; i++)
		sv[i] = new double [num_v * 2];
	for (i = 0; i < num_l; i++) {
		for (j = 0; j < num_v; j++) 
			sv[i][j] = system[i][j];
		for (; j < num_l * 2; j++)
			if (i + num_v == j)
				if (way)
					sv[i][j] = 1;
				else
					sv[i][j] = -1;
			else
				sv[i][j] = 0;
	}
	istr = new double [num_v * 2];
	bv = new double *[num_l];
	for (i = 0; i < num_l; i++) {
		bv[i] = new double [2];
		bv[i][0] = i + num_v;
		bv[i][1] = fm[i];
	}
	for (i = 0; i < num_v * 2; i++)
		if (i < num_v)
			istr[i] = function[i] * -1;
		else
			istr[i] = 0;
	for (i = 0; i < num_v * 2 - 1; i++) {
		if (istr[i] < 0)
			if (fabs(istr[i + 1]) > fabs(istr[i]))
				i_lcol = i + 1;
	}
	th = new double [num_l];
	for (i = 0; i < num_l; i++)
		th[i] = bv[i][1] / sv[i][i_lcol];
	for (i = 0; i < num_l - 1; i++)
		if (th[i] > th[i + 1])
			i_lrow = i + 1;
	alm = sv[i_lrow][i_lcol];
	print_result_to_file(0);
}
bool simplex::plane_is_valid()
{
	int i;
	bool result = true;
	if (way)
		for (i = 0; i < num_v * 2; i++)
			if (istr[i] < 0) {
				result = false;
				break;
			}
	return result;
}
bool simplex::function_is_undefined()
{
	int i;
	bool result = true;
	for (i = 0; i < num_l; i++)
		if (th[i] < 0) {
			result = false;
			break;
		}
	return result;
}
void simplex::gen_plane()
{
	int i, j, it_num = 0;
	double A, B;
	while (!plane_is_valid()) { 
	// && !function_is_undefined()) {
	// TODO: нужно сделать проверку на валидность функции.
	A = bv[i_lrow][1];
	B = istr[i_lcol];
	func -= A * B / alm;
	double *tmp_bv = new double [num_l];
	bv [i_lrow][0] = i_lcol;
	A = bv[i_lrow][1];
	for (i = 0; i < num_v; i++) {
		B = sv[i][i_lcol];
		tmp_bv[i] = bv[i_lrow][1];
		if (i != i_lrow)
			tmp_bv[i] = bv[i][1] - A * B / alm;
		else
			tmp_bv[i] /= alm;
	}
	for (i = 0; i < num_v; i++)
		bv[i][1] = tmp_bv[i];
	double *tmp_istr = istr;
	B = istr[i_lcol];
	for (i = 0; i < num_v * 2; i++) {
		A = sv[i_lrow][i];
		tmp_istr[i] = istr[i] - A * B / alm;
	}
	istr = tmp_istr;
	double **tmp_sv = new double *[num_v];
	for (i = 0; i < num_v; i++)
		tmp_sv[i] = new double [num_v * 2];
	for (i = 0; i < num_l; i++)
		for (j = 0; j < num_v * 2; j++) {
			tmp_sv[i][j] = sv[i][j];
			A = sv[i_lrow][j];
			B = sv[i][i_lcol];
			if (i == i_lrow)
				tmp_sv[i][j] /= alm;
			else
				tmp_sv[i][j] = sv[i][j] - A * B / alm;
		}
	sv = tmp_sv;
	i_lcol = 0;
	for (i = 0; i < num_l; i++)
		th[i] = bv[i][1] / sv[i][i_lcol];
	i_lrow = 0;
	for (i = 0; i < num_l -1; i++)
		if (th[i] > th[i + 1])
			i_lrow = i + 1;
		alm = sv[i_lrow][i_lcol];
		it_num++;
		print_result_to_file(it_num);
	}

	cout << "\nf(x) = " << func << "\n" << endl;
	for (i = 0; i < num_v; i++) {
		cout << "x" << bv[i][0] + 1 << " = " << bv[i][1] << endl;
	}
	cout << "\nВсе вычисления были записаны в файл table.txt\n" << endl;
}
void simplex::print_result_to_file(int it_num) 
{
	int i, j;
	if (!it_num) {
	table << "Задана целевая функция:\n" << endl;
	std::stringstream f_x;
	f_x << "f(x) = ";
	for (i = 0; i < num_v; i++) {
		if (!i)
			f_x << function[i] << "x" << i + 1 << " ";
		else {
			if (function[i] < 0)
				f_x << "- " << fabs(function[i]) << "x" << i + 1 << " ";
			if (function[i] > 0)
				f_x << "+ " << function[i] << "x" << i + 1 << " ";
		}
	}
	std::string minmax;
	if (way)
		minmax = "max";
	else
		minmax = "min";
	f_x << "=> " << minmax << "\n" << endl;
	table << f_x.str();
	table << "И система ограничений:\n" << endl;
	std::stringstream math_sys;
	std::string math_sign;
	for (i = 0; i < num_l; i++) {
		for (j = 0; j < num_v; j++) {
			if (!j)
				math_sys << system[i][j] << "x" << j + 1 << " ";
			else
				if (system[i][j] == 1)
					if (!j)
						math_sys << "x" << j + 1 << " ";
					else
						math_sys << "+ x" << j + 1 << " ";
				else
					if (system[i][j] == -1)
					if (!j)
						math_sys << "-x" << j + 1 << " ";
					else
						math_sys << "- x" << j + 1 << " ";
					else {
						if (system[i][j] < 0)
							math_sys << "- " << fabs(system[i][j])<< "x" << j + 1 << " ";
						else
							math_sys << "+ " << system[i][j] << "x" << i + 1 << " ";
						if (!sign[i])
								math_sign = "<=";
						if (sign[i] == 1)
							math_sign = "=";
						 if (sign[i] == 2)
							math_sign = ">=";
				}
		}

		math_sys << math_sign << " " << fm[i];
		math_sys << endl;
	}
	std::string min_or_max;
	if (way)
		min_or_max = "максимум";
	else
		min_or_max = "минимум";
	table << math_sys.str() << endl;
	table << "Решим данную задачу на " << min_or_max << " методом симплексных таблиц.\nПостроим первый опорный план:\n" << endl;
	}
	for (i = 0; i < num_l; i++) {

		table << "x" << bv[i][0] + 1 << "\t" << bv[i][1] << "\t";
		for (j = 0; j < num_v * 2; j++)
			table << sv[i][j] << "\t";
		if (!plane_is_valid())
			table << th[i];
		table << "\n" << endl;
	}
	table << "f(x)\t" << func << "\t";
	for (i = 0; i < num_v * 2; i++)
		table << istr[i] << "\t";
	table << "\n";
	if (plane_is_valid()) {
		if (plane_is_valid())
			table << "\nДанный план является оптимальным и не требует улучшения. Решение найдено." << endl;
			std::ofstream outfile ("table.txt");
			outfile << table.str();
	}
	else {
		std::string ln_or_gn;
		if (way)
			ln_or_gn = "неположительные";
		else
			ln_or_gn = "положительные";
		std::stringstream num_of_plane;
		if (!it_num)
			num_of_plane << "Первый опорный план";
		else
			num_of_plane << it_num + 1 << "-й план также";
		table << "\n" << num_of_plane.str() << " не является оптимальным, поскольку\nв индексной строке присутствуют " << ln_or_gn << " элементы.\nErо необходимо улучшить.\n" << endl;
	}

}
