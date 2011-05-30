#include <string>
#include <iostream>

#include "get_data_from_user.h"
#include "Out.h"

void get_data_from_user(struct _userdata* ud)
{
	std::string buf, ineq;
	const char* err;
	unsigned int err_pos;

	_out << std::cout << "Введите функцию (например -1x0 + 2x1 -> max):\n\n";
	do {
		getline(std::cin, buf);
		_out << std::cout << "\n";
		if (0 != (err = eqparser::parse(buf.c_str(), &ud->func, &err_pos, eqparser::func)))
			_out << std::cout << err_pos << ": " << err << " [функция не принята, попробуйте ещё раз]\n\n";
		   
	} while (err);
	eqparser::recreate_ineq(&ud->func, &ineq, eqparser::func);
	_out << std::cout << "Функция принята [" << ineq.c_str() << "]\n\n";

	err = 0;
	_out << std::cout << "Введите систему ограничений (по одному неравенству вида 1x0 + 2x1 >= 10 в строку), по окончании введите пустую строку (нажмите <enter>).\n\n";
	for (;;) {
		getline(std::cin, buf);
		_out << std::cout << "\n";
		if (buf.compare("") == 0) {
			if (ud->system.size() < 2) {
				_out << std::cout << "Вы не можете указать меньше двух ограничений\n\n";
				continue;
			} else
				break;
		}
		if (!err)
			ud->system.push_back(new struct eqparser::_eq);
		if (0 != (err = eqparser::parse(buf.c_str(), ud->system.back(), &err_pos, eqparser::ineq))) 
			_out << std::cout << err_pos << ": " << err << " [ограничение не принято, попробуйте ещё раз (пустая строка означает конец ввода)]\n\n";
		else {
			eqparser::recreate_ineq(ud->system.back(), &ineq, eqparser::ineq);
			_out << std::cout << "Ограничение принято [" << ineq.c_str() << "], введите следующее\n\n";
		}
	}
}

