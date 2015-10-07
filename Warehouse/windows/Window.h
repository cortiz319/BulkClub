#ifndef WINDOWS_WINDOW_H_
#define WINDOWS_WINDOW_H_

#include <iostream>
#include "../member/Member.h"
#include "../util/Item.h"
#include "../util/Trip.h"
#include "../gui/zahnrad.h"

using namespace std;

class Window {
private:
	bool set, update;
	int ID_c;
protected:
	int *purchases_a_day;
	Item **items;
	int *num_items;
	Member **members;
	int num_members;
	Trip **trips;
	int num_days;
public:
	void * return_val;
	int ID;
	Window(int *p_a_d, Item ** i, int *n_i, Member **m,
			int n_m, Trip **t, int n_d) {
		update_data(p_a_d, i, n_i, m, n_m, t, n_d);
		set = false;
		ID_c = 0;
		return_val = NULL;
		ID = -1;
		update = false;
	}
	void issue_update() {
		update = true;
	}
	bool do_update() {
		if (update) {
			update = false;
			return true;
		}
		return false;
	}
	void update_data(int *p_a_d, Item ** i, int *n_i,
			Member **m, int n_m, Trip **t, int n_d) {
		purchases_a_day = p_a_d;
		items = i;
		num_items = n_i;
		members = m;
		num_members = n_m;
		trips = t;
		num_days = n_d;
	}
	void set_data(int *&p_a_d, Item **&i, int *&n_i,
			Member **&m, int n_m, Trip **&t, int n_d) {
		p_a_d = purchases_a_day;
		i = items;
		n_i = num_items;
		m = members;
		n_m = num_members;
		t = trips;
		n_d = num_days;
	}
	virtual ~Window() {}
	virtual void render_main(zr_window *) = 0;
	void changeWindow(int ID) {
		set = true;
		ID_c = ID;
	}
	int setWindow() {
		if (set) {
			set = false;
			return ID_c;
		}
		return ID;
	}
};

#endif /* WINDOWS_WINDOW_H_ */
