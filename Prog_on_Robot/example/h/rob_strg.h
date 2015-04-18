/*
 * rob_strg.h
 *
 *  Created on: 24.03.2015
 *      Author: mk
 */

#ifndef C_H_ROB_STRG_H_
#define C_H_ROB_STRG_H_




#include <stdlib.h>
#include "kernel.h"
/* Will be generated: */
#include "kernel_id.h"
#include "ecrobot_interface.h"


#include "search.h"
#include "card.h"
#include "list.h"
#include "settings.h"

int orientation = 0;
/*
void change_direction(int new_o){
	r.orient += new_o;
}*/

void ecrobot_device_initialize(void) {
}

void ecrobot_device_terminate(void) {
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
}

void print_string(int x, int y, char *msg) {
	display_goto_xy(x, y);
	display_string(msg);
	display_update();
}

void print_int(int x, int y, int value) {
	display_goto_xy(x, y);
	display_int(value, 1);
	display_update();
}

void beep() {
	ecrobot_sound_tone(220, 100, 100);
}

void init() {
	print_string(0, 2, "-----------");
	print_string(0, 3, " ERROR bot ");
	print_string(0, 4, "-----------");
	ecrobot_set_light_sensor_active(NXT_PORT_S4);
}

int is_line() {
	return ecrobot_get_light_sensor(NXT_PORT_S4) > 550; //ehemals 600
}

void wait(unsigned long int ms) {
	systick_wait_ms(ms);
}


void stop_motor() {
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	wait(100);
}

void move(int speed) {
	nxt_motor_set_speed(NXT_PORT_B, speed, 1);
	nxt_motor_set_speed(NXT_PORT_C, speed, 1);
}

/*
 * Links herum rotieren
 * degree: Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 */
void rotate_l(int degree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (degree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}

}

/*
 * Links herum rotieren bis Linie erreicht
 * degree: Maximaler Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 * return: Gibt zurÃ¼ck, ob Linie erkannt wurde
 */
int rotate_to_line_l(int maxdegree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (maxdegree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
		if (is_line()){
			stop_motor();
			return 1;
		}
	}
	return 0;
}

/*
 * Rechts herum rotieren
 * degree: Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 */
void rotate_r(int degree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (degree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, -speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}

}

/*
 * Rechts herum rotieren bis Linie erreicht
 * degree: Maximaler Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 * return: Gibt zurÃ¼ck, ob Linie erkannt wurde
 */
int rotate_to_line_r(int maxdegree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (maxdegree / 90. * winkelconst);
	while (status) {
	status = 0;
					if (nxt_motor_get_count(NXT_PORT_B) > -w_degree) {
						nxt_motor_set_speed(NXT_PORT_B, -speed, 1);
						status = 1;
					} else {
						nxt_motor_set_speed(NXT_PORT_B, 0, 1);
					}
					if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
						nxt_motor_set_speed(NXT_PORT_C, speed, 1);
						status = 1;
					} else {
						nxt_motor_set_speed(NXT_PORT_C, 0, 1);
					}
		if (is_line()){
			stop_motor();
			return 1;
		}

	}
	return 0;
}

/*
 * Gibt zurÃ¼ck, ob BerÃ¼hungssensor betÃ¤tigt
 */
int touched(){
	return ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S2) || ecrobot_get_touch_sensor(NXT_PORT_S3);
}

/*
 * Aufgaben, die beim Erkennen eines Tokens ausgefÃ¼hrt werden sollen:
 */
void token_found(){
	stop_motor();			// Anhalten
	token++;				// Counter hochzÃ¤hlen
	beep();					// Piepen, 1s bei 220 Hz
	wait(10000);			// 10s warten


}

/*
 * Linienfindung:
 * Eingabe:  Suchradius in grad
 * RÃ¼ckgabe: 	0... keine Linie gefunden
 * 				1... Linie gefunden
 * 	pendelt zuerst nach links, dann nach rechts
 */
int search_line(int max) {
	int found = 0;
	int speed = 40;
	found = rotate_to_line_l(max, speed);
	found =is_line();

	wait(200);
	if (found == 1) { return 1;}
	else {found=rotate_to_line_r(3*max, speed);}

	if (found == 0){
		found = rotate_to_line_l(4*max, speed);

	}
	if (found == 0){
		rotate_r(2*max, speed);

		}

	wait(200);
	return found;

}

/*
 * In die Kreuzung einfahren
 */
void junction(int speed) {
	int status = 1;
	int w_degree = 225;
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}
}

/*
 * Kreuzung untersuchen
 * RÃ¼ckgabe: 	entdeckte Abzweige, Codierung siehe #defines,
 * 				in globalen Himmelsrichtungen
 */
int exploration(){
	int found_left;
	int found_right;
	int found_forward;
	int found_control;

	int exp_speed = speedconst;

	rotate_l(45, exp_speed);

	found_forward = rotate_to_line_r(90, exp_speed);

	//print_int(0,0,found_forward);
	wait(50);
	if (found_forward){
		rotate_r(45, exp_speed);
	}

	found_right = rotate_to_line_r(90, exp_speed);
	wait(50);
		if (found_right){
			rotate_r(45, exp_speed);
		}



	found_control = rotate_to_line_r(90, exp_speed);
	wait(50);
	if (found_control){
			rotate_r(45, exp_speed);
		}



	found_left = rotate_to_line_r(100, exp_speed); //ehemals 135
	wait(50);
	if (found_left){
			rotate_r(90, exp_speed);
		} else {rotate_r(30, exp_speed);}
		display_clear(0);

		if (found_left){
			print_string(1, 1, "LINKS");
		}

		if (found_right){
			print_string(1, 3, "RECHTS");
		}

		if (found_forward){
			print_string(1, 5, "GERADEAUS");
		}

		if (found_control){
			print_string(1, 4, "Hinten");
		}

		int found_north = 0;
		int found_east  = 0;
		int found_south = 0;
		int found_west  = 0;

		if(found_forward){
			switch(orientation) {
					case 0: found_north = 1; break;
					case 1: found_east  = 1; break;
					case 2: found_south = 1; break;
					case 3: found_west  = 1; break;
				}
		}
		if(found_right){
				switch(orientation) {
					case 3: found_north = 1; break;
					case 0: found_east  = 1; break;
					case 1: found_south = 1; break;
					case 2: found_west  = 1; break;
				}
		}
		if(found_control){
				switch(orientation) {
					case 2: found_north = 1; break;
					case 3: found_east  = 1; break;
					case 0: found_south = 1; break;
					case 1: found_west  = 1; break;
				}
		}

		if(found_left){
				switch(orientation) {
					case 1: found_north = 1; break;
					case 2: found_east  = 1; break;
					case 3: found_south = 1; break;
					case 0: found_west  = 1; break;
				}
		}

		int back;
		back = found_north*No + found_south*So + found_east*Ea + found_west*We;
		print_int(3, 7, back);
		return back;
}

/*
 * Funktion lÃ¤sst Roboter nach links abbiegen
 */

void turn_left(){
	int found;
	rotate_l(45,speedconst);
	found = rotate_to_line_l(90,speedconst);

	//change_direction(-1);
	//print_string(0,7,"Richtung");
	//print_int(9,7, r.orient);

}

void turn_right(){
	int found;
	rotate_r(45,speedconst);
	found = rotate_to_line_r(90,speedconst);

	//change_direction(1);
	//print_string(0,7,"Richtung");
	//print_int(9,7, r.orient);

}

void turn_back(){
	int found;
	rotate_r(135,65);
	found = rotate_to_line_r(90,speedconst);

	//change_direction(2);
	//print_string(0,7,"Richtung");
	//print_int(9,7, r.orient);

}

void turn_forward(){
	int found;
	found = rotate_to_line_l(30,speedconst);
	found = rotate_to_line_r(130,speedconst);

}



void turn_north(){
	switch(r.orient) {
		case MYNORTH: turn_forward(); break;
		case MYEAST: turn_left(); break;
		case MYSOUTH: turn_back(); break;
		case MYWEST: turn_right(); break;
	}
	r.orient = MYNORTH;
}
void turn_west(){
	switch(r.orient) {
		case MYWEST: turn_forward(); break;
		case MYNORTH: turn_left(); break;
		case MYEAST: turn_back(); break;
		case MYSOUTH: turn_right(); break;
	}
	r.orient = MYWEST;
}
void turn_south(){
	switch(r.orient) {
		case MYSOUTH: turn_forward(); break;
		case MYWEST: turn_left(); break;
		case MYNORTH: turn_back(); break;
		case MYEAST: turn_right(); break;
	}
	r.orient = MYSOUTH;
}
void turn_east(){
	switch(r.orient) {
		case MYEAST: turn_forward(); break;
		case MYSOUTH: turn_left(); break;
		case MYWEST: turn_back(); break;
		case MYNORTH: turn_right(); break;
	}
	r.orient = MYEAST;
}

void drive_to_crossroad(){
	nxt_motor_set_count(NXT_PORT_B, 0);
	int speedy = 60;
	print_string(0,7,"Richtung");
	print_int(9,7, r.orient);
	while(1){

		if (is_line()) {
			move(speedy); //65
			if(nxt_motor_get_count(NXT_PORT_B) < 300){
				move(speedy+15);//80
				wait(30); //100
			}

			wait(10); // 30
			if (touched()) {
				//display_clear(0);
				print_string(0, 3, "Token gefunden");
				token_found();
			}

		} else {

				if (!search_line(8)) {
					stop_motor();
					display_clear(0);
					print_string(0,1,"Kreuzung entdeckt");

					junction(junctionspeed); //65
					wait(200);
					//beep();
					break;
				}
			}

	}
}


void Robot_Move(int direction){
	switch(direction) {
			case MYSOUTH: turn_south(); break;
			case MYNORTH: turn_north(); break;
			case MYWEST:  turn_west(); break;
			case MYEAST:  turn_east(); break;
		}
	drive_to_crossroad();

}



void turn_north2(){
	switch(r.orient) {
		case MYNORTH: break;
		case MYEAST: rotate_l(90,speedconst); break;
		case MYSOUTH: rotate_l(180,speedconst); break;
		case MYWEST: rotate_r(90,speedconst); break;
	}
	r.orient = MYNORTH;
}
void turn_west2(){
	switch(r.orient) {
		case MYWEST:  break;
		case MYNORTH: rotate_l(90,speedconst); break;
		case MYEAST: rotate_l(180,speedconst); break;
		case MYSOUTH: rotate_r(90,speedconst); break;
	}
	r.orient = MYWEST;
}
void turn_south2(){
	switch(r.orient) {
		case MYSOUTH:  break;
		case MYWEST: rotate_l(90,speedconst); break;
		case MYNORTH: rotate_l(180,speedconst); break;
		case MYEAST: rotate_r(90,speedconst); break;
	}
	r.orient = MYSOUTH;
}
void turn_east2(){
	switch(r.orient) {
		case MYEAST:break;
		case MYSOUTH: rotate_l(90,speedconst); break;
		case MYWEST: rotate_l(180,speedconst); break;
		case MYNORTH: rotate_r(90,speedconst); break;
	}
	r.orient = MYEAST;
}

int search_only(int dir) {
	switch (dir) {
	case MYNORTH:
		turn_north2();
		rotate_l(30, SPEED);
		if (rotate_to_line_r(60, SPEED)) {
			return No;
		}
		else {
			rotate_l(30, SPEED);
			return 0;
		}

	case MYSOUTH:
		turn_south2();
		rotate_l(30, SPEED);
		if (rotate_to_line_r(60, SPEED)) {
					return So;
				}
				else {
					rotate_l(30, SPEED);
					return 0;
				}
	case MYWEST:
		turn_west2();
		rotate_l(30, SPEED);
		if (rotate_to_line_r(60, SPEED)) {
					return We;
				}
				else {
					rotate_l(30, SPEED);
					return 0;
				}
	case MYEAST:
		turn_east2();
		rotate_l(30, SPEED);
		if (rotate_to_line_r(60, SPEED)) {
					return Ea;
				}
				else {
					rotate_l(30, SPEED);
					return 0;
				}
	default:
		return 0;
	}
}



int search_intersec(intersec *i) {
	int back_val = 0;
	switch (r.orient) {
	case MYNORTH:
		if (!i->West) back_val  += search_only(MYWEST);
		if (!i->North) back_val += search_only(MYNORTH);
		if (!i->East) back_val  += search_only(MYEAST);
		if (!i->South) back_val += search_only(MYSOUTH);
		break;
	case MYSOUTH:
		if (!i->West) back_val  += search_only(MYWEST);
		if (!i->South) back_val += search_only(MYSOUTH);
		if (!i->East) back_val  += search_only(MYEAST);
		if (!i->North) back_val += search_only(MYNORTH);
		break;
	case MYWEST:
		if (!i->North) back_val += search_only(MYNORTH);
		if (!i->West) back_val  += search_only(MYWEST);
		if (!i->South) back_val += search_only(MYSOUTH);
		if (!i->East) back_val  += search_only(MYEAST);
		break;
	case MYEAST:
		if (!i->South) back_val += search_only(MYSOUTH);
		if (!i->East) back_val  += search_only(MYEAST);
		if (!i->North) back_val += search_only(MYNORTH);
		if (!i->West) back_val  += search_only(MYWEST);

	break;

	}
	return back_val;
}




intersec convert_intersec_to_dir(intersec *ex, int saved_or) {
	intersec i;
	i.North=0;
	i.East = 0;
	i.West = 0;
	switch (saved_or) {
	case MYNORTH:
		if (ex->North) i.North = 1;
		if (ex->West) i.West = 1;
		if (ex->East) i.East = 1;
		break;
	case MYSOUTH:
		if (ex->South) i.North = 1;
		if (ex->East) i.West = 1;
		if (ex->West) i.East = 1;
		break;
	case MYWEST:
		if (ex->West) i.North = 1;
		if (ex->South) i.West = 1;
		if (ex->North) i.East = 1;
		break;
	case MYEAST:
		if (ex->East) i.North = 1;
		if (ex->North) i.West = 1;
		if (ex->South) i.East = 1;
		break;
	}
	return i;
}



int Robot_GetIntersections(int x, int y){
	int back, saved_or;
	intersec i, display_opt;
	dechiff_intersec(&i, x);
	saved_or = r.orient;
	back = x + search_intersec(&i);
	dechiff_intersec(&i, back-y);
	display_opt = convert_intersec_to_dir(&i, saved_or);
	display_clear(0);
	if (display_opt.North) print_string(1, 5, "GERADEAUS");
	if (display_opt.West) print_string(1, 1, "LINKS");
	if (display_opt.East) print_string(1, 3, "RECHTS");
	return back;
}


void set_robot(robot *r){
	point p;
	p.x = 0;
	p.y = 0;
	r->cur_pos = p;
	r->sel_dir = MYNORTH;
	r->no_cross = 0;
	r->orient = MYNORTH;
}

#endif /* C_H_ROB_STRG_H_ */
