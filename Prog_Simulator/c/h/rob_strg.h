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


/*
void change_direction(int new_o){
	r.orient += new_o;
}*/

void ecrobot_device_initialize(void) {
}

void ecrobot_device_terminate(void) {
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
	print_string(0, 3, "Project - X");
	print_string(0, 4, "-----------");
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
}

int is_line() {
	int i;
	int help=0;
	for (i=0; i<2;i++){
		help += ecrobot_get_light_sensor(NXT_PORT_S3);
	}
	help /=2;
	return help > 550; //ehemals 600
}

void wait(unsigned long int ms) {
	systick_wait_ms(ms);
}


void stop_motor() {
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
}

void move(int speed) {
	nxt_motor_set_speed(NXT_PORT_B, speed, 0);
	nxt_motor_set_speed(NXT_PORT_C, speed, 0);
}

void rotate_l(int degree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (degree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}

}

int rotate_to_line_l(int maxdegree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (maxdegree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 0);
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

void rotate_r(int degree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (degree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, -speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}

}

int rotate_to_line_r(int maxdegree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (maxdegree / 90. * winkelconst);
	while (status) {
	status = 0;
					if (nxt_motor_get_count(NXT_PORT_B) > -w_degree) {
						nxt_motor_set_speed(NXT_PORT_B, -speed, 0);
						status = 1;
					} else {
						nxt_motor_set_speed(NXT_PORT_B, 0, 1);
					}
					if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
						nxt_motor_set_speed(NXT_PORT_C, speed, 0);
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

int touched(){
	return ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S2) || ecrobot_get_touch_sensor(NXT_PORT_S4);
}

void token_found(){
	stop_motor();			// Anhalten
	token++;				// Counter hochzählen
	beep();					// Piepen, 1s bei 220 Hz
	wait(10000);			// 10s warten

	//token counter aufrufen!!!

}

/*
 * Linienfindung:
 * Eingabe:  Suchradius in grad
 * Rückgabe: 	0... keine Linie gefunden
 * 				1... Linie gefunden
 * 	pendelt zuerst nach links, dann nach rechts
 */
int search_line(int max) {
	int found = 0;

	found = rotate_to_line_l(max, 65);
	found =is_line();

	wait(200);
	if (found == 1) { return 1;}
	else {found=rotate_to_line_r(3*max, 65);}

	if (found == 0){
		found = rotate_to_line_l(4*max, 65);

	}
	if (found == 0){
		rotate_r(2*max, 65);

		}

	wait(200);
	return found;

}

void junction(int speed) {
	int status = 1;
	int w_degree = 225;
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}
}

/*
int exploration(){
	int found_left;
	int found_right;
	int found_forward;
	int found_control;

	int exp_speed = 65;

	rotate_l(45, exp_speed);

	found_forward = rotate_to_line_r(90, exp_speed);

	if (found_forward){
		rotate_r(45, exp_speed);
	}

	found_right = rotate_to_line_r(90, exp_speed);
		if (found_right){
			rotate_r(45, exp_speed);
		}

	found_control = rotate_to_line_r(90, exp_speed);
		if (found_control){
			rotate_r(45, exp_speed);
		}

	found_left = rotate_to_line_r(135, exp_speed);
		if (found_left){
			rotate_r(90, exp_speed);
		}
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
		//print_int(3, 7, back);
		return back;
}*/

void turn_left(){
	int found;
	rotate_l(45,65);
	found = rotate_to_line_l(90,65);
	while (found ==0){
		beep();
		wait(100);
	}
	//change_direction(-1);
	print_string(0,7,"Richtung");
	print_int(9,7, r.orient);

}

void turn_right(){
	int found;
	rotate_r(45,65);
	found = rotate_to_line_r(90,65);
	while (found ==0){
		beep();
		wait(100);
	}
	//change_direction(1);
	print_string(0,7,"Richtung");
	print_int(9,7, r.orient);

}

void turn_back(){
	int found;
	rotate_r(135,65);
	found = rotate_to_line_r(90,65);
	while (found ==0){
		beep();
		wait(100);
	}
	//change_direction(2);
	print_string(0,7,"Richtung");
	print_int(9,7, r.orient);

}

void turn_forward(){
	int found;
	rotate_l(30,65);
	found = rotate_to_line_r(130,65);
	while (found ==0){
		beep();
		wait(100);
	}
	print_string(0,7,"Richtung");
	print_int(9,7, r.orient);

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
	while(1){

		int line_state;
		if (is_line()) {
			move(65);
			if(nxt_motor_get_count(NXT_PORT_B) < 300){
				move(80);
				wait(100);
			}
			wait(30);
			if (touched()) {
				print_string(0, 3, "Token gefunden");
				token_found();
			}

		} else {
				stop_motor();
				line_state = search_line(5);

				if (line_state ==0) {
					display_clear(0);
					print_string(0,1,"Kreuzung entdeckt");

					junction(65);
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


int search_only(int dir) {
	switch (dir) {
	case MYNORTH:
		turn_north();
		rotate_l(30, SPEED);
		if (rotate_to_line_r(60, SPEED)) {
			return No;
		}
		else {
			rotate_l(30, SPEED);
			return 0;
		}

	case MYSOUTH:
		turn_south();
		rotate_l(30, SPEED);
		if (rotate_to_line_r(60, SPEED)) {
					return So;
				}
				else {
					rotate_l(30, SPEED);
					return 0;
				}
	case MYWEST:
		turn_west();
		rotate_l(30, SPEED);
		if (rotate_to_line_r(60, SPEED)) {
					return We;
				}
				else {
					rotate_l(30, SPEED);
					return 0;
				}
	case MYEAST:
		turn_east();
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
	if (i->North) back_val += search_only(MYNORTH);
	if (i->East) back_val += search_only(MYEAST);
	if (i->South) back_val += search_only(MYWEST);
	if (i->West) back_val += search_only(MYSOUTH);
	return back_val;
}


int Robot_GetIntersections(int x){
	intersec i;
	dechiff_intersec(&i, x);
	return search_intersec(&i);
}








void set_robot(robot *r){
	point p;
	p.x = 0;
	p.y = 0;
	r->cur_pos = p;
	r->sel_dir = MYNORTH;
	r->no_cross = 0;
}



















#endif /* C_H_ROB_STRG_H_ */
