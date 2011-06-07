#ifndef _TABLE_HH_
#define _TABLE_HH_

#include <iterator>
#include "eqparser.hh"
#include "cells.hh"

namespace table {

	template <class T>
	class matrix {
		T *buf;
		unsigned int x, y;
	public:
		matrix(unsigned int _x, unsigned int _y);
		~matrix();
		T* at(unsigned int, unsigned int);
	};

	enum _rowtype { ineq, f, m };
	enum _coltype { nbv, sv, av, fm, all, theta }; // non-basis vars, slack vars, artificial var, free member
	enum celltype { nbv_name };

	class CommonData {
	public:
		matrix<cells::cell*>* m;
		// TODO: this is bad
		unsigned int amount[3]; // _coltype
		cells::cell** get_cell(unsigned int, unsigned int);
		unsigned int block_start(enum _coltype);
		unsigned int block_end(enum _coltype);
	};

	class _column {
		CommonData* cd;
	public:
		unsigned int column;
		void init(CommonData* _cd, unsigned int _column) { cd = _cd; column = _column; }
		bool operator!=(const _column& c) { return column != c.column; }
		void operator++() { column++; }
	};

	class _row {
		CommonData* cd;
	public:
		unsigned int row;
		void init(CommonData* _cd, unsigned int _row) { cd = _cd; row = _row; }
		void add_nbv(struct eqparser::var&, int = 1);
		void add_fm(double, int = 1);
		void add_av();
		void add_sv(int = 1);
		void add_sbv(cells::cell*);
		bool operator!=(const _row& r) { return row != r.row; }
		void operator++() { row++; }
	};

	class table : public CommonData {
	public:
		table();
		void init_matrix(unsigned int, unsigned int);

		template <class T>
		class iterator : public std::iterator<std::output_iterator_tag, T> {
			T t;
		public:
			iterator() {}
			iterator(table* tab, unsigned int i) { t.init(tab, i); }
			iterator(const iterator<T>& it) :t(it.t) {}
			iterator& operator++() { ++t; return *this; }
			bool operator!=(const iterator<T>& it) { return t != it.t; }
			T& operator*() { return t; }
		};

		iterator<_row> names_row() { return iterator<_row>(this, 0); }
		iterator<_row> rows_begin() { return iterator<_row>(this, 1); }
		iterator<_row> rows_end() { return iterator<_row>(this, 1+amount[nbv]); }
		iterator<_row> z_row() { return iterator<_row>(this, 1+amount[nbv]); }
		iterator<_column> names_column() { return iterator<_column>(this, 0); }
		iterator<_column> begin(enum _coltype ct) { return iterator<_column>(this, block_start(ct)); }
		iterator<_column> end(enum _coltype ct) { return iterator<_column>(this, block_end(ct)); }

		void add_nbv(unsigned int);
		cells::cell* get_av(iterator<_row>&);
		cells::cell* get_sv(iterator<_row>&);
		cells::cell** get_cell(iterator<_row>&, iterator<_column>&);

		table& operator=(table&);
	};

} /* namespace table */

#endif /* _TABLE_HH_ */
