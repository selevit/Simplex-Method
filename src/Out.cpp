#include <iostream>
#include <map>

#include "cp866strings.h"
#include "Out.h"

Out& Out::operator<<(double d)
{
	if (can_output)
		std::cout << d;

	return *this;
}

Out& Out::operator<<(const char* s)
{
	if (can_output) {
		if (use_cp866)
			s = uni_to_cp866(s);
		std::cout << s;
	}

	return *this;
}

Out::Out() : use_cp866(false), can_output(true)
{
	conv.table.insert(std::pair("Оптимальный план найден. Количество итераций = ", CP866_OPTIMAL_PLANE_FOUND));
	conv_table.insert(std::pair("Целевая функция не ограничена. Задача с данным условием не имеет решений.", CP866_FUNCTION_UNDEFINED));
	conv_table.insert(std::pair("Данная задача имеет решение, но оно не является оптимальным.", CP866_NON_OPTIMAL_SOLUTION));
	conv_table.insert(std::pair("Введите значение свободного члена для ", CP866_ENTER_FREE_MEMBER));
	conv_table.insert(std::pair("-го неравенства: ", CP866_DASHGO_EQUATION));
	conv_table.insert(std::pair("Введите коэффициент при X", CP866_ENTER_X));
	conv_table.insert(std::pair("Введите коэффициент целевой функции при X", CP866_ENTER_X_FACTOR));
	conv_table.insert(std::pair(" для ", CP866_FOR));
	conv_table.insert(std::pair("Введите количество основных переменных задачи: ", CP866_ENTER_AMOUNT_OF_VARIABLES));
	conv_table.insert(std::pair("Введите направление целевой функции (max, min): ", CP866_ENTER_FUNCTION_DIRECTION));
	conv_table.insert(std::pair("Вы ввели недопустимое значение.", CP866_WRONG_VALUE));
}

const char* Out::uni_to_cp866(const char* s)
{
	return conv_table[s];
}

Out out;
