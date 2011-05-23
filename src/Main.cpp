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

#include <cstring>
#include "Simplex.h"
#include "Out.h"

int main(int argc, char* argv[])
{
	Simplex s;
	if (argc > 1 && !strcmp("-t", argv[1]))
		s.input_interactive = false;
#ifdef _WIN32
	else
		_out.use_cp866 = true;
#endif
	s.getAndSetInputData();  
	s.init();
	s.setValues();

	return 0;
}
