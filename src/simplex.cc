#include <list>

#include "simplex.hh"
#include "eqparser.hh"
#include "table.hh"

namespace simplex {

	namespace {
		typedef std::list<std::list<std::string> > lls;

		void lls_append(table::table* t, lls* _lls)
		{
		}

		void show_results(lls* _lls)
		{
		}
	} /* anon namespace */

	void run(struct user_data::_userdata* ud)
	{
		unsigned int rows, columns;
		user_data::_system::iterator sit;
		eqparser::_vars::iterator vit;
		table::table *new_table, *old_table, *t;
		table::table::iterator<table::_row> rit, rit1, rit2;
		table::table::iterator<table::_column> cit;
		cells::cell **c, *c1;
		lls out;

		new_table = new table::table;

		new_table->amount[table::nbv] = ud->func.vars.size(); // количество небазисных переменных смотрим по функции
	
		new_table->amount[table::sv] = 0;
		for (sit = ud->system.begin(); sit != ud->system.end(); ++sit)
			if ((*sit)->sign != eqparser::equal) // для уравнений не нужны слаки
				new_table->amount[table::sv]++;

		columns = new_table->amount[table::nbv] + new_table->amount[table::sv];
		new_table->amount[table::av] = 0;
		for (sit = ud->system.begin(); sit != ud->system.end(); ++sit)
			if ((*sit)->sign != eqparser::le)
			{
				columns++; // для каждой искусственной переменной
				new_table->amount[table::av]++;
			}
		columns++; // для свободных членов

		rows = new_table->amount[table::sv]; // ряд для каждого ограничения
		rows++; // для z-функции

		new_table->init_matrix(rows, columns);

		// таблица должна знать имена nbv
		for (vit = ud->func.vars.begin(); vit != ud->func.vars.end(); ++vit)
			new_table->add_nbv((*vit).b);

		for (rit = new_table->rows_begin(), sit = ud->system.begin(); /* rit != new_table->rows_end(), */ sit != ud->system.end(); ++sit, ++rit) {
			for (vit = (*sit)->vars.begin(); vit != (*sit)->vars.end(); ++vit) {
				if ((*sit)->sign == eqparser::ge) {
					(*rit).add_nbv(*vit, -1);
				} else
					(*rit).add_nbv(*vit);
			}
			if ((*sit)->sign == eqparser::ge)
				(*rit).add_sv(-1); // должен добавлять имя и 0 в функцию
			else if ((*sit)->sign == eqparser::le)
				(*rit).add_sv(); // аналогично
			if ((*sit)->sign != eqparser::le)
				(*rit).add_av(); // то же что и выше
			if ((*sit)->sign == eqparser::ge)
				(*rit).add_fm((*sit)->rval, -1);
			else
				(*rit).add_fm((*sit)->rval);
		}

		// задать горизонтальные имена - задаются при add-ах
		// задать функцию (с -М по надобности) - тоже
		// задать вертикальные начальные базисные переменные
		for (rit = new_table->rows_begin(); rit != new_table->rows_end(); ++rit) {
			if (0 != (c1 = new_table->get_av(rit)))
				(*rit).add_sbv(c1);
			else // если у нас нет искусственной переменной используем слак
				(*rit).add_sbv(new_table->get_sv(rit));
		}

		// посчитать z-row
		// TODO: ЭТО ВСЁ ГОВНО ДОЛЖНО БЫТЬ СПРЯТАНО В TABLE!!!!
		rit1 = new_table->z_row();
		rit2 = new_table->names_row();
		for (cit = new_table->begin(table::all); cit != new_table->end(table::all); ++cit) {
			c = new_table->get_cell(rit1, cit);
			if (*c == 0) {
				if (new_table->amount[table::av] != 0)
					*c = new cells::bigm;
				else
					*c = new cells::var;
			}
			**c = **new_table->get_cell(rit2, cit);
			for (rit = new_table->rows_begin(); rit != new_table->rows_end(); ++rit) {
				// cj - zj
				**c -= **new_table->get_cell(rit, cit);
			}
		}

		old_table = new table::table;
		*old_table = *new_table;

		return;

		for (;;) {
			// if (have_solution) break;
			// calculate theta row
			lls_append(new_table, &out);
			t = new_table; new_table = old_table; old_table = t; // TODO: вернуться к этому позже
			// find pivot
			// create row operations
			// apply ro to rows
			// recalculate z-string
		}

		lls_append(new_table, &out);
		show_results(&out);
	}

} /* namespace simplex */
