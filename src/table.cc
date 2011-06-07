#include "table.hh"

namespace table {

	template <class T>
	matrix<T>::matrix(unsigned int _x, unsigned int _y) : x(_x), y(_y)
	{
		unsigned int i;

		buf = new T[_x * _y];
		for (i = 0; i < x * y; ++i) {
			buf[i] = 0;
		}
	}

	template <class T>
	T* matrix<T>::at(unsigned int _x, unsigned int _y)
	{
		return &buf[y*_x + _y];
	}

	template <class T>
	matrix<T>::~matrix()
	{
		delete[] buf;
	}

	cells::cell** CommonData::get_cell(unsigned int row, unsigned int column)
	{
		return m->at(row, column);
	}

	unsigned int CommonData::block_start(enum _coltype ct)
	{
		unsigned int s = 1;

		if (ct == all)
			return s;

		s += amount[nbv];
		if (ct == sv)
			return s;

		s += amount[sv];
		if (ct == av)
			return s;

		s += amount[av];
		if (ct == fm)
			return s;

		return 0;
	}

	unsigned int CommonData::block_end(enum _coltype ct)
	{
		unsigned int s = 1;

		s += amount[nbv];
		if (ct == nbv)
			return s;

		s += amount[sv];
		if (ct == sv)
			return s;

		s += amount[av];
		if (ct == av)
			return s;

		s += amount[fm];
		if (ct == all)
			return s;

		return 0;
	}

	void _row::add_nbv(struct eqparser::var& v, int factor)
	{
		cells::cell** c;
		table::iterator<_column> cit;
		table* t = static_cast<table*>(cd);

		for (cit = t->begin(nbv); cit != t->end(nbv); ++cit) {
			c = cd->get_cell(row, (*cit).column);
			if (*c != 0 && (static_cast<cells::border<cells::var>*>(*c))->var_index == v.b)
				break;
		}
		// этот цикл ДОЛЖЕН выходить брейком
		// если он выходит по i == 1 + cd->amount[nbv], то это пиздец и жопа а мы оказались на слаке
		// с другой стороны тут мы доверяем парсеру (которому СЕЙЧАС НЕЛЬЗЯ доверять)
		// TODO: переобдумать

		c = cd->get_cell(row, (*cit).column);
		if (*c == 0)
			*c = new cells::var;
		**c = v.a * factor; 
	}

	void _row::add_fm(double val, int factor)
	{
		cells::cell** c = cd->get_cell(row, cd->block_start(fm));
		if (*c == 0)
			*c = new cells::var;
		**c = val * factor;
	}

	void _row::add_av()
	{
		static unsigned int av_set = 0;
		unsigned int column;
		cells::cell **c, **name_c;

		column = cd->block_start(av)+av_set;
		c = cd->get_cell(row, column);
		name_c = cd->get_cell(0, column);
		if (*c == 0) {
			*c = new cells::var;
			*name_c = new cells::border<cells::bigm>('m', av_set+1);
		}
		**c = 1;
		av_set++; // TODO: это уёбищно и надо сделать как-то по другому
	}

	void _row::add_sbv(cells::cell* c)
	{
		*cd->get_cell(row, 0) = c; // в принципе это можно копировать
	}

	void _row::add_sv(int factor)
	{
		static unsigned int sv_set = 0;
		unsigned int column;
		cells::cell **c, **name_c;

		column = cd->block_start(sv)+sv_set;
		c = cd->get_cell(row, column);
		name_c = cd->get_cell(0, column);
		if (*c == 0) { // это по идее всегда true
			*c = new cells::var;
			*name_c = new cells::border<cells::var>('s', sv_set+1);
		}
		**c = factor;
		sv_set++;
	}

	cells::cell* table::get_av(iterator<_row>& rit)
	{
		cells::cell** c;
		iterator<_column> cit;

		for (cit = begin(av); cit != end(av); ++cit) {
			c = get_cell(rit, cit);
			if (*c != 0)
				return *c;
		}
	
		return 0;
	}

	cells::cell* table::get_sv(iterator<_row>& rit)
	{
		cells::cell** c;
		iterator<_column> cit;

		for (cit = begin(sv); cit != end(sv); ++cit) {
			c = get_cell(rit, cit);
			if (*c != 0)
				return *c;
		}

		return 0; // по идее до этого никогда не должно дойти
	}

	cells::cell** table::get_cell(iterator<_row>& rit, iterator<_column>& cit)
	{
		return CommonData::get_cell((*rit).row, (*cit).column);
	}

	void table::add_nbv(unsigned int index)
	{
		// это добавка небазисной переменной в горизонтальный ряд с именами
		static unsigned int i = 0; // TODO: тоже уёбищно

		*m->at(0, 1+i) = new cells::border<cells::var>('x', index);
		i++; // если у нас сбоил цикл в simplex.cpp мы вылетаем прямо на соседний слак
	}

	void table::init_matrix(unsigned int rows, unsigned int columns)
	{
		m = new matrix<cells::cell*>(rows+1, columns+1); // +1 для имён (cells::border)
	}

	table& table::operator=(table& t)
	{
		return *this;
	}

} /* namespace table */
