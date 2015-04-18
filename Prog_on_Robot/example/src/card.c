/*
 * card.c
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#include <stdlib.h>
#include <stdio.h>

#include "../h/card.h"





int koord_to_i(int x, int y) {
	int i;
	if ((x<(-(COL-1)/2))||(x>(COL-1)/2)||(y<(-(COL-1)/2))||(y>(COL-1)/2)) {
		//printf("ERROR over range\n");
		return 0;
	}
	x += (COL-1)/2;
	y -= (COL-1)/2;
	y = -y;
	i = y*COL + x;
	return i;
}

void init_card(card *c) {
	int i;
	for (i=0;i<ROW*COL;i++) {
		c->map[i] = 0;
	}

	c->map[START] = 1;
	c->cur_pos = START;
	c->cur_e = 0;
	c->cur_n = 0;
	c->cur_s = 0;
	c->cur_w = 0;
}


int get_state(card *c, int x, int y) {
	int i = koord_to_i(x,y);
	return c->map[i];
}
void set_state(card *c, int x, int y, int state) {
	int i = koord_to_i(x,y);
	c->map[i] = state;
}



void set_local_envoriment(card* c, int x, int y) {
	intersec state;
	dechiff_intersec(&state, c->map[koord_to_i(x,y)]);
	if ((state.North)&&(!get_state(c, x,y+1))) c->map[koord_to_i(x, y+1)]=1;
	if ((state.South)&&(!get_state(c, x,y-1))) c->map[koord_to_i(x, y-1)]=1;
	if ((state.West)&&(!get_state(c, x-1,y))) c->map[koord_to_i(x-1, y)]=1;
	if ((state.East)&&(!get_state(c, x+1,y))) c->map[koord_to_i(x+1, y)]=1;
}


void set_global_enviroment(card* c) {
	int x, y;
	for (x = -hrow; x<=hrow; x++) {
		for (y=-hcol; y<=hcol; y++) {
			set_local_envoriment(c, x, y);
		}
	}
}


void i_to_koord(point *p, int i) {
	p->x = i%(ROW-1) - hcol;
	p->y = -((i- (p->x + hcol))/(ROW-1))+hrow;
}

int exists_unkown(card *c) {
	int bool = 0;
	int i;
	for (i = 0; i<ROW*COL; i++) {
		if (c->map[i] == 1)
			bool++;
	}
	return bool;
}

void set_unkown_to_void(card *c) {
	c->map[START] = 5050;
}

void set_h_wall(card* c, int y, int opt) {
	int i;
	int wall_opt = 0;
	if (opt==MYNORTH) wall_opt = WALL_N;
	if (opt==MYSOUTH) wall_opt = WALL_S;
	for (i=-hcol;i<=hcol;i++) {
		set_state(c, i, y, wall_opt);
	}
	c->wall_h++;
}

void set_v_wall(card* c, int x, int opt) {
	int i;
	int wall_opt = 0;
	if (opt==MYEAST) wall_opt = WALL_E;
	if (opt==MYWEST) wall_opt = WALL_W;
	for (i=-hrow;i<=hrow;i++) {
		set_state(c, x, i, wall_opt);
	}
	c->wall_v++;
}

void update_border(card* c, point p) {
	if (p.x<c->cur_w) c->cur_w = p.x;
	if (p.x>c->cur_e) c->cur_e = p.x;
	if (p.y>c->cur_n) c->cur_n = p.y;
	if (p.y<c->cur_s) c->cur_s = p.y;

	if ((c->cur_e - c->cur_w)==SIZEX-1) {
		set_v_wall(c, c->cur_e+1, MYEAST);
		set_v_wall(c, c->cur_w-1, MYWEST);
	}
	if ((c->cur_n - c->cur_s)==SIZEY-1) {
			set_h_wall(c, c->cur_n+1, MYNORTH);
			set_h_wall(c, c->cur_s-1, MYSOUTH);
		}
}


