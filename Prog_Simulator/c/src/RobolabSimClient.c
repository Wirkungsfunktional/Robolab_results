
#include "../h/Configuration.h"
#include "search.h"
#include "/home/mk/Dokumente/robo_prak/robolab15_g28/simulation_code_18_03/robo_sim/c/h/list.h"
#include "../h/card.h"
#include "../h/settings.h"





void set_robot(robot *r) {
	point start_p;
	start_p.x = 0;
	start_p.y =0;
	Robot_Move(0, 0);
	r->cur_pos = start_p;
	r->sel_dir = MYNORTH;
	r->no_cross = 0;
	r->orient = MYNORTH;
	r->angle = 0;
}



int main(void) {


	init_logfile(&logbook);
	set_robot(&r);
	runbot(&r);
	printf("EXIT");


	return EXIT_SUCCESS;
}
