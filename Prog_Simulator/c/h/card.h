/*
 * card.h
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#ifndef C_H_CARD_H_
#define C_H_CARD_H_


#include "search.h"
#include "settings.h"



typedef struct card {
	int map[ROW*COL];
	int cur_pos;
	int wall_v, wall_h;
	int cur_w, cur_e, cur_n, cur_s;
} card;


void init_card(card*);
void set_state(card*, int, int, int);
void print_card(card*);
void print_row(card*, int);
int get_state(card*, int, int);
void set_global_envoriment(card*);
void set_local_envoriment(card*, int, int);
int koord_to_i(int, int);
void i_to_koord(point *p, int i);
int exists_unkown(card*);
void set_unkown_to_void(card*);
void set_h_wall(card*, int, int);
void set_v_wall(card*, int, int);
void update_border(card*, point);






#endif /* C_H_CARD_H_ */
