#include <iostream>
// #include "Windows.h"

class A
{
public:
	static const int i = 10;
	int a;
	A() { std::cout << i << std::endl; };
};

int main()
{
//	int width = WideCharToMultiByte(866, 0, L"Юникод строка", -1, 0, 0, NULL, NULL);
//	char *buf = new char[width];
//	WideCharToMultiByte(866, 0, L"Юникод строка", -1, buf, 0, NULL, NULL);
//	std::cout << ываbuf << std::endl;

	A* p1 = new A;
	p1->a = 12;
	std::cout << p1->a << std::endl;
	A* p2 = (A*) operator new (sizeof(A));

	A* p;
	new (p) A;
	p->a = 11;
	std::cout << p->a << std::endl;

	return 0;
}
