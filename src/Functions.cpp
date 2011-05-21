#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "cp866strings.h"
#include "Functions.h"

void Functions::die(char* msg, int exit_code)
{
	std::cerr << msg << std::endl;
	exit(exit_code);
}

#ifdef _WIN32

char * Functions::_(char * s)
{
	if (!use_cp866)
		return s;

	if (!strncmp(s, "Оптимальный план найден. Количество итераций = ", 1))
		return CP866_OPTIMAL_PLANE_FOUND;

	if (!strncmp(s, "Целевая функция не ограничена. Задача с данным условием не имеет решений.", 1))
		return CP866_FUNCTION_UNDEFINED;

	if (!strncmp(s, "Данная задача имеет решение, но оно не является оптимальным.", 1))
		return CP866_NON_OPTIMAL_SOLUTION;

	if (!strncmp(s, "Выберите метод ввода (вручную - 1, из файла - 2): ", 3))
		return CP866_SELECT_INPUT_METHOD;

	if (!strncmp(s, "Введите имя или путь к входному файлу: ", 9))
		return CP866_ENTER_PATH_TO_FILE;

	if (!strncmp(s, "Введите значение свободного члена для ", 9))
		return CP866_ENTER_FREE_MEMBER;

	if (!strncmp(s, "-го неравенства: ", 3))
		return CP866_DASHGO_EQUATION;

	if (!strncmp(s, "Введите коэффициент при X", 11))
		return CP866_ENTER_X;

	if (!strncmp(s, " для ", 3))
		return CP866_FOR;

	if (!strncmp(s, "Введите количество основных переменных задачи: ", 11))
		return CP866_ENTER_AMOUNT_OF_VARIABLES;

	if (!strncmp(s, "Введите направление целевой функции (max, min): ", 10))
		return CP866_ENTER_FUNCTION_DIRECTION;

	if (!strncmp(s, "Возникла непредвиненная ошибка. попробуйте еще раз.", 10))
		return CP866_UNDEFINED_ERROR;

	if (!strncmp(s, "Вы ввели недопустимое значение.", 3))
		return CP866_WRONG_VALUE;

	if (!strncmp(s, "Нет доступа к файлу!", 1))
		return CP866_CANNOT_ACCESS_FILE;

	return 0;
}

#endif /* _WIN32 */
