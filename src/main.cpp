/*
 * Эта программа реализует решение систем
 * уравнений линейного программирования
 * с помощью симплекс метода.
 * Задание выполнено для куросовой работы
 * Выполнил Студент Волгоградского Технологического
 * колледжа кафедры Программного обеспечения
 * вычислительной техники и автоматизированных
 * систем группы ВТ-3-1 В учебный период
 */ 

#include <string>
#include <sstream>
#include <list>
#include <iostream>
#include <cmath>

#include "Out.h"
#include "eqparser.h"
// #include "Simplex.h"

const char* recreate_ineq(struct eqparser::_eq* eq, enum eqparser::_eqtype et)
{
	std::stringstream s;
	eqparser::_vars::iterator it;

	for (it = eq->vars.begin(); it != eq->vars.end(); it++) {
		if (it != eq->vars.begin()) {
			if ((*it).a < 0)
				s << "- " << fabs((*it).a);
			else
				s << "+ " << (*it).a;
		} else
			s << (*it).a;
		s << "x" << (*it).b << " ";
	}
	if (et == eqparser::func) {
		s << "-> ";
		if (eq->l == eqparser::max)
			s << "max";
		else // eq->l == eqparser::min
			s << "min";
	} else { // et == eqparser::ineq
		switch (eq->sign) {
		case eqparser::equal:
			s << "= ";
			break;
		case eqparser::le:
			s << "<= ";
			break;
		case eqparser::ge:
			s << ">= ";
			break;
		default:
			break;
		}
		s << eq->rval;
	}
	s << '\0';
	return s.str().c_str();
}

int main()
{
	std::string buf;
	const char* err;
	unsigned int err_pos;

	struct {
		struct eqparser::_eq func;
		std::list<struct eqparser::_eq*> system;
	} userdata;

	_out << std::cout << "Введите функцию (например -1x0 + 2x1 -> max):\n\n";
	do {
		getline(std::cin, buf);
		_out << std::cout << "\n";
		if (0 != (err = eqparser::parse(buf.c_str(), &userdata.func, &err_pos, eqparser::func)))
			_out << std::cout << err_pos << ": " << err << " [функция не принята, попробуйте ещё раз]\n\n";
		   
	} while (err);
	_out << std::cout << "Функция принята [" << recreate_ineq(&userdata.func, eqparser::func) << "]\n\n";

	err = 0;
	_out << std::cout << "Введите систему ограничений (по одному неравенству вида 1x0 + 2x1 >= 10 в строку), по окончании введите пустую строку (нажмите <enter>).\n\n";
	for (;;) {
		getline(std::cin, buf);
		_out << std::cout << "\n";
		if (buf.compare("") == 0) {
			if (userdata.system.size() < 2) {
				_out << std::cout << "Вы не можете указать меньше двух ограничений\n\n";
				continue;
			} else
				break;
		}
		if (!err)
			userdata.system.push_back(new struct eqparser::_eq);
		if (0 != (err = eqparser::parse(buf.c_str(), userdata.system.back(), &err_pos, eqparser::ineq)))
			_out << std::cout << err_pos << ": " << err << " [ограничение не принято, попробуйте ещё раз (пустая строка означает конец ввода)]\n\n";
		else
			_out << std::cout << "Ограничение принято [" << recreate_ineq(userdata.system.back(), eqparser::ineq) << "], введите следующее\n\n";
	}
	

//	Simplex s;
//	s.get_data_from_user();
//	s.run();

	return 0;
}
