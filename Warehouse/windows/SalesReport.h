#ifndef WINDOWS_SALESREPORT_H_
#define WINDOWS_SALESREPORT_H_

#include "../core/Initializer.h"
#include <string>
#include <sstream>

namespace patch1
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#include "Window.h"

class SalesReport : public Window {

private:
//	zr_edit_box eb;
//	zr_char edit_buffer[MAX_BUFFER];


	char ** values;
	char ** days;
	zr_size selected, size, selected_days;
	zr_state active, active_d;
	int state;
	int fail;
public:
	SalesReport(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = SALESREPORT;
		state = 0;
		fail = 0;

		size = 3;
		values = new char*[size];
		days = new char*[num_days];
		selected = 0;
		selected_days = 0;
		active = false;
		active_d = false;

		values[0] = "Default";
		values[1] = "Regular";
		values[2] = "Executive";

		days[0] = "Day 1";
		days[1] = "Day 2";
		days[2] = "Day 3";
		days[3] = "Day 4";
		days[4] = "Day 5";

//		for(int i = 0 ; i < num_days; i++)
//		{
//			string day = patch1::to_string(i+1);
//			string day_s = "Day" + day;
//			days[i] = "days";
//		}

	}
	~SalesReport(){}
	void render_main(zr_window *window);
};



#endif /* WINDOWS_SALESREPORT_H_ */
