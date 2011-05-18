#include <iostream>
#include "Matrix.h"

int main()
{
	using namespace std;

	matrix<int> m(1,5);
	matrix<int> n(1,5);
	m[1][1] = 10;
	n = m;
	cout << n[1][1] << endl;

	return 0;
}
