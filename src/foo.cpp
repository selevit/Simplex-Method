#include <iostream>
#include "Windows.h"

int main()
{
	int width = WideCharToMultiByte(866, 0, L"Юникод строка", -1, 0, 0, NULL, NULL);
	char *buf = new char[width];
	WideCharToMultiByte(866, 0, L"Юникод строка", -1, buf, 0, NULL, NULL);
	std::cout << buf << std::endl;

	return 0;
}
