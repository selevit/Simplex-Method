#include "simplex.h"

int main()
{
	simplex *ud = new simplex;
	ud->get_data_from_user();
	ud->init();
	ud->gen_plane();
	return 0;
}
