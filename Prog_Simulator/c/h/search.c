/*
 * search.c
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#include <stdlib.h>
#include <stdio.h>


#include "search.h"

int token = 0; // weg------------------------------------------------------------------------


//point start_point;
card c;
//card visit_points;


int invert(int i) {
	switch (i) {
	case MYSOUTH: return MYNORTH;
	case MYNORTH: return MYSOUTH;
	case MYWEST: return MYEAST;
	case MYEAST: return MYWEST;
	default: return 0;
	}
}

void set_inter(intersec *i,int n, int e, int s, int w, int opt) {
    i->North = n;
    i->East = e;
    i->South = s;
    i->West = w;
    i->searched = opt;
}

void dechiff_intersec(intersec *i, int x) {
    switch (x) {
    case 16:
    	set_inter(i, 1,0,0,0,0); break;
    case 32:
    	set_inter(i, 0,0,1,0,0); break;
    case 48:
    	set_inter(i, 1,0,1,0,0);break;
    case 64:
    	set_inter(i, 0,0,0,1,0);break;
    case 80:
    	set_inter(i, 1,0,0,1,0);break;
    case 96:
    	set_inter(i, 0,0,1,1,0);break;
    case 112:
    	set_inter(i, 1,0,1,1,0);break;
    case 128:
    	set_inter(i, 0,1,0,0,0);break;
    case 144:
    	set_inter(i, 1,1,0,0,0);break;
    case 160:
    	set_inter(i, 0,1,1,0,0);break;
    case 176:
    	set_inter(i, 1,1,1,0,0);break;
    case 192:
    	set_inter(i, 0,1,0,1,0);break;
    case 208:
    	set_inter(i, 1,1,0,1,0);break;
    case 224:
    	set_inter(i, 0,1,1,1,0);break;
    case 240:
    	set_inter(i, 1,1,1,1,0);break;
    case 0:
    	set_inter(i, 0,0,0,0,0);break;
    case 1:
    	set_inter(i, 0,0,0,0,1);break;
    case WALL_N:
    	set_inter(i, 0,0,0,0,0);break;
    case WALL_S:
        set_inter(i, 0,0,0,0,0);break;
    case WALL_E:
        set_inter(i, 0,0,0,0,0);break;
    case WALL_W:
        set_inter(i, 0,0,0,0,0);break;
    default:
    	break;
    	//printf("ERROR in dechiff_inter");
    }

}

int state_to_cross(intersec *i) {
	return (i->North+i->West+i->East+i->South);
}

nearfield_ana max(nearfield_ana a, nearfield_ana b) {
	if (a.count==0) return b;
	if (b.count==0) return a;

	if (a.count<b.count) return b;
	else return a;
}

point ana_nearfield(card *c, analyzer *a) {
	int count;
	nearfield_ana back_value;
	if (a->North.p.x!=-133) {
		count = 0;
		if (c->map[koord_to_i(a->North.p.x+1, a->North.p.y)]>0) count++;
		if (c->map[koord_to_i(a->North.p.x-1, a->North.p.y)]>0) count++;
		if (c->map[koord_to_i(a->North.p.x, a->North.p.y+1)]>0) count++;
		if (c->map[koord_to_i(a->North.p.x, a->North.p.y-1)]>0) count++;
		a->North.count = count;
	}
	if (a->South.p.x!=-133) {
			count = 0;
			if (c->map[koord_to_i(a->South.p.x+1, a->South.p.y)]>0) count++;
			if (c->map[koord_to_i(a->South.p.x-1, a->South.p.y)]>0) count++;
			if (c->map[koord_to_i(a->South.p.x, a->South.p.y+1)]>0) count++;
			if (c->map[koord_to_i(a->South.p.x, a->South.p.y-1)]>0) count++;
			a->South.count = count;
		}
	if (a->East.p.x!=-133) {
			count = 0;
			if (c->map[koord_to_i(a->East.p.x+1, a->East.p.y)]>0) count++;
			if (c->map[koord_to_i(a->East.p.x-1, a->East.p.y)]>0) count++;
			if (c->map[koord_to_i(a->East.p.x, a->East.p.y+1)]>0) count++;
			if (c->map[koord_to_i(a->East.p.x, a->East.p.y-1)]>0) count++;
			a->East.count = count;
		}
	if (a->West.p.x!=-133) {
			count = 0;
			if (c->map[koord_to_i(a->West.p.x+1, a->West.p.y)]>0) count++;
			if (c->map[koord_to_i(a->West.p.x-1, a->West.p.y)]>0) count++;
			if (c->map[koord_to_i(a->West.p.x, a->West.p.y+1)]>0) count++;
			if (c->map[koord_to_i(a->West.p.x, a->West.p.y-1)]>0) count++;
			a->West.count = count;
		}
	back_value = max(a->North, max(a->South, max(a->West, a->East)));
	return back_value.p;

}

void init_intersec(intersec *i) {
	i->North = 0;
	i->South = 0;
	i->West = 0;
	i->East = 0;
}

int analyse_enviroment(card* c, int x, int y) {
	int new_val = 0;
	intersec cross_N, cross_S, cross_W, cross_E;
	dechiff_intersec(&cross_N, c->map[koord_to_i(x,y+1)]);
	dechiff_intersec(&cross_S, c->map[koord_to_i(x,y-1)]);
	dechiff_intersec(&cross_E, c->map[koord_to_i(x+1,y)]);
	dechiff_intersec(&cross_W, c->map[koord_to_i(x-1,y)]);
	if (cross_N.South) new_val += No;
	if (cross_S.North) new_val += So;
	if (cross_W.East) new_val += We;
	if (cross_E.West) new_val += Ea;
	return new_val;
}

point calc_point_by_dir(point p, int dir){
	switch (dir) {
	case MYNORTH:
		p.y++;
		break;
	case MYSOUTH:
		p.y--; break;
	case MYEAST:
		p.x++; break;
	case MYWEST:
		p.x--; break;
	}
	return p;
}

void move_step_back(point p) {
	int dir = invert(pop_from_logfile(&logbook));
	point new_p = calc_point_by_dir(p, dir);
	Robot_Move(new_p.x,new_p.y);
	// dir = invert(dir);
	Robot_Move(p.x,p.y);
	r.cur_pos = p;
	add_to_logfile(&logbook, dir);

}

void matching_error(point p) {
	//printf("Measurement failed by (%i, %i) \n", p.x, p.y);
	move_step_back(p);
}

int move_back_to_fail(point p) {
	int dir = invert(pop_from_logfile(&logbook));
	point new_p = calc_point_by_dir(p, dir);
	Robot_Move(new_p.x,new_p.y);
	set_state(&c, p.x, p.y, 0);
	r.cur_pos = new_p;
	return Robot_GetIntersections();

}

int match_enviroment(card *c,point cur_p, int state){
	int x = cur_p.x;
	int y = cur_p.y;
	int counter = 0;
	int new_intersec;
	intersec cross_N, cross_S, cross_W, cross_E, cross_cur;
	dechiff_intersec(&cross_cur, state);
	if (c->map[koord_to_i(x,y+1)]>1) {
		dechiff_intersec(&cross_N, c->map[koord_to_i(x,y+1)]);
		if (cross_cur.North!=cross_N.South)counter++;
	}
	if (c->map[koord_to_i(x,y-1)]>1) {
			dechiff_intersec(&cross_S, c->map[koord_to_i(x,y-1)]);
			if (cross_cur.South!=cross_S.North)counter++;
		}
	if (c->map[koord_to_i(x+1,y)]>1) {
			dechiff_intersec(&cross_E, c->map[koord_to_i(x+1,y)]);
			if (cross_cur.East!=cross_E.West)counter++;
		}
	if (c->map[koord_to_i(x-1,y)]>1) {
			dechiff_intersec(&cross_W, c->map[koord_to_i(x-1,y)]);
			if (cross_cur.West!=cross_W.East) counter++;
		}

	if (counter){
		//matching_error(cur_p);
		new_intersec = Robot_GetIntersections();
		/*if (new_intersec == state) {
			//printf("This was not enough\n");
			while ((new_intersec == c->map[koord_to_i(r.cur_pos.x, r.cur_pos.y)])||c->map[koord_to_i(r.cur_pos.x, r.cur_pos.y)]==0) {
				new_intersec = move_back_to_fail(cur_p);
			}
			set_global_enviroment(c);
			//printf("fail was at (%i, %i) \n", r.cur_pos.x, r.cur_pos.y);
			//print_card(c);
		}*/

		return new_intersec;
	}
	else {
		return state;
	}
}

void set_hypothesis(card *c) {
	int x,y, new_val;
	for (x=-hcol;x<hcol;x++) {
		for (y=-hrow;y<hrow;y++) {
			if (c->map[koord_to_i(x,y)] == 1){
				new_val = analyse_enviroment(c, x, y);
				c->map[koord_to_i(x,y)] = new_val;
			}
		}
	}

}


int allowed_way(int opt, int code) {
	int erg = 0;
	intersec i;
	dechiff_intersec(&i, code);
	switch (opt) {
	case MYSOUTH:
		return i.South;
		break;
	case MYNORTH:
		return i.North;
		break;
	case MYWEST:
		return i.West;
		break;
	case MYEAST:
		return i.East;
		break;
	default:
		break;
		//printf("ERROR in allowed_way");
	}
	return erg;
}

int calc_dir_by_points(point p1, point p2) {
	if (p1.x<p2.x) return MYEAST;
	if (p1.x>p2.x) return MYWEST;
	if (p1.y<p2.y) return MYNORTH;
	if (p1.y>p2.y) return MYSOUTH;
	return 0;

}

point get_next_point(point p, card *c, int* dir) {
	point new_p;
	point cur_p = p;
	analyzer a;
	*dir =0;
	init_analyzer(&a);
	if ((get_state(c, p.x, p.y-1)==1)&&allowed_way(MYSOUTH, c->map[koord_to_i(p.x, p.y)])){
		new_p.x = p.x;
		new_p.y = p.y-1;
		set_nearfield_ana(&a, new_p, MYSOUTH);
	}
	if ((get_state(c, p.x, p.y+1)==1)&&allowed_way(MYNORTH, c->map[koord_to_i(p.x, p.y)])){
			new_p.x = p.x;
			new_p.y = p.y+1;
			set_nearfield_ana(&a, new_p, MYNORTH);
		}
	if ((get_state(c, p.x-1, p.y)==1)&&allowed_way(MYWEST, c->map[koord_to_i(p.x, p.y)])){
			new_p.x = p.x-1;
			new_p.y = p.y;
			set_nearfield_ana(&a, new_p, MYWEST);
		}
	if ((get_state(c, p.x+1, p.y)==1)&&allowed_way(MYEAST, c->map[koord_to_i(p.x, p.y)])){
			new_p.x = p.x+1;
			new_p.y = p.y;
			set_nearfield_ana(&a, new_p, MYEAST);
		}
	if (a.active){
		p = ana_nearfield(c, &a);
		*dir = calc_dir_by_points(cur_p, p);
	}
	return p;
}

int rob_mv(int x, int y) {
	int erg;
	//visit_points.map[koord_to_i(x,y)]--;
	erg = Robot_Move(x, y);
	return erg;
}

void move_robot(robot *r) {
	point cur_p = r->cur_pos;
	int dir, tok;
	point new_p = get_next_point(r->cur_pos, &c, &dir);
	if (comp_p(cur_p, new_p)) {
		r->sel_dir = MYBREAK;
		return;
	}
	tok = rob_mv(new_p.x, new_p.y);  //dir
	add_to_logfile(&logbook, dir);
	if (tok==2) {
		token++;
	}
	r->cur_pos = new_p;
}

void move_rek(list_elem l) { //rekursives bewegen mittels BSF-Tree
	if (l->parent->parent!=NULL) move_rek(l->parent);
	add_to_logfile(&logbook, invert(l->in));
	rob_mv(l->p.x, l->p.y);
	return;
}

point get_local_nearest_point(point in_p, card *c, int s) {
	int search_for = s;
	int breaker = 0;
	queue q;
	list_elem new_elem, cur_elem;
	point p, new_p;
	intersec cross;
	p.x = 0; p.y=0;
	init_queue(&q, in_p);
	if (!exists_unkown(c)&&(token!=TOKEN)) {
		//token = TOKEN;
		c->map[START] = search_for;
		p.x = 0; p.y=0;
		delete_queue(&q);
		return p;
	}
	while (breaker != search_for) {
		cur_elem = get_front(&q);
		p = cur_elem->p;
		breaker = c->map[koord_to_i(p.x, p.y)];
		if (breaker == search_for ) {
			q.found_elem  = cur_elem;
			pop_queue(&q);
			break;
		}
		dechiff_intersec(&cross, breaker);
		if((cross.North)&&(cur_elem->in!=MYNORTH)) {
			new_p = cur_elem->p;
			new_p.y++;
			new_elem = make_follower(MYSOUTH, new_p, cur_elem);
			push_queue(&q, new_elem);
		}
		if ((cross.South)&&(cur_elem->in!=MYSOUTH)) {
			new_p = cur_elem->p;
			new_p.y--;
			new_elem = make_follower(MYNORTH, new_p, cur_elem);
			push_queue(&q, new_elem);
			}
		if ((cross.West)&&(cur_elem->in!=MYWEST)) {
			new_p = cur_elem->p;
			new_p.x--;
			new_elem = make_follower(MYEAST, new_p, cur_elem);
			push_queue(&q, new_elem);
		}
		if ((cross.East)&&(cur_elem->in!=MYEAST)) {
			new_p = cur_elem->p;
			new_p.x++;
			new_elem = make_follower(MYWEST, new_p, cur_elem);
			push_queue(&q, new_elem);
		}
		pop_queue(&q);
	}
	move_rek(q.found_elem);
	delete_queue(&q);
	return p;
}


int breaker = 1;

void run_by_card(robot *r) {
	//point return_p, test_p; test_p.x = 0; test_p.y = -4;
	int state;
	//if (comp_p(r->cur_pos, test_p)&&breaker) {
	//	state = 48;
	//	breaker = 0;
	//}
	//else {
	int new_val1, new_val2;
	new_val1 = analyse_enviroment(&c, r->cur_pos.x, r->cur_pos.y); ///////////////////////////////////////
	new_val2 = analyse_never_exist(&c, r->cur_pos.x, r->cur_pos.y);
	new_val1 += new_val2;

	state = Robot_GetIntersections();
	//state -= new_val2;
	//}
	intersec in;
	//state = match_enviroment(&c, r->cur_pos, state);
	dechiff_intersec(&in, state);

	set_state(&c, r->cur_pos.x, r->cur_pos.y, state);
	//set_state(&visit_points, r->cur_pos.x, r->cur_pos.y, state_to_cross(&in));
	set_local_envoriment(&c, r->cur_pos.x, r->cur_pos.y);
	move_robot(r);

}

void runbot(robot *r) {
	point return_p;
	int state, exit_1 = 0;
	intersec in;
	init_card(&c);
	while (token != TOKEN) {
		update_border(&c, r->cur_pos);
		run_by_card(r);

		if (r->sel_dir==MYBREAK) {
				r->sel_dir = 2;
				return_p = get_local_nearest_point(r->cur_pos, &c, 1);
				r->cur_pos= return_p;
				if ((r->cur_pos.x==0)&&(r->cur_pos.y==0)){
					token = TOKEN;
					exit_1 = 1;
				}

			}
	}

	if (!exit_1) {
		state = Robot_GetIntersections(); ////////////////////////////////////////////////////////////
		dechiff_intersec(&in, state);
		set_state(&c, r->cur_pos.x, r->cur_pos.y, state);
		//set_state(&visit_points, r->cur_pos.x, r->cur_pos.y, state_to_cross(&in));
		set_local_envoriment(&c, r->cur_pos.x, r->cur_pos.y);
		set_hypothesis(&c);
		set_unkown_to_void(&c);
		get_local_nearest_point(r->cur_pos, &c, 5050);
	}

	delete_logfile(&logbook);
	//printf("EXIT SUCCESS");

}



int analyse_never_exist(card* c, int x, int y) {
	int new_val = 0;
	intersec cross_N, cross_S, cross_W, cross_E;
	if (c->map[koord_to_i(x,y+1)]>1) {
		dechiff_intersec(&cross_N, c->map[koord_to_i(x,y+1)]);
		if (!cross_N.South) new_val += No;
	}
	if (c->map[koord_to_i(x,y-1)]>1) {
		dechiff_intersec(&cross_S, c->map[koord_to_i(x,y-1)]);
		if (!cross_S.North) new_val += So;
	}
	if (c->map[koord_to_i(x+1,y)]>1) {
		dechiff_intersec(&cross_E, c->map[koord_to_i(x+1,y)]);
		if (!cross_E.West) new_val += Ea;
	}
	if (c->map[koord_to_i(x-1,y)]>1) {
		dechiff_intersec(&cross_W, c->map[koord_to_i(x-1,y)]);
		if (!cross_W.East) new_val += We;
	}
	return new_val;
}

/*
int get_intersec(int calc_cross) {
	int back_val = calc_cross;
	intersec i;
	dechiff_intersec(&i, 240-calc_cross);
	if (calc_cross == 0) {
		return explorate_orientation(0);
	}
	//if (!i.North) back_val += explorate_orientation(MYNORTH);
	//if (!i.East) back_val += explorate_orientation(MYEAST);
	//if (!i.South) back_val += explorate_orientation(MYSOUTH);
	//if (!i.West) back_val += explorate_orientation(MYWEST);
	return back_val;
}*/






