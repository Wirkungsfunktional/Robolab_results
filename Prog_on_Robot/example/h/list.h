/*
 * list.h
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#ifndef LIST_H_
#define LIST_H_


#include "../h/settings.h"




typedef struct point {
	int x,y;
}point;

typedef struct intersec {
    int North, West, East, South, searched;
}intersec;

typedef struct robot {
	point cur_pos;
	int sel_dir, no_cross;
	int orient;
} robot;

typedef struct l_elem *list_elem;
typedef struct l_elem {
	point p;
	list_elem next, parent;
	int in;
} l_elem;


typedef struct queue {
	list_elem start, end, hidden_start;
	list_elem found_elem;
	int size;
} queue;

typedef struct nearfield_ana {
	point p;
	int count;
}nearfield_ana;

typedef struct analyzer {
	nearfield_ana North, South, West, East;
	int active;
} analyzer;


typedef struct stack_elem *stack;
typedef struct stack_elem {
	int direction;
	stack next;
}stack_elem;

typedef struct logfile {
	stack start;
	int size;
} logfile;





void push_queue(queue*, list_elem);
void pop_queue(queue*);
void delete_queue(queue*);
void init_queue(queue*, point);
list_elem get_front(queue*);
list_elem make_follower(int, point, list_elem);
void print_back(queue*, int);
void set_nearfield_ana(analyzer*, point, int);
void init_analyzer(analyzer*);


void init_logfile(logfile*);
void add_to_logfile(logfile*, int);
int pop_from_logfile(logfile*);
void delete_logfile(logfile*);
int comp_p(point, point);




#endif /* LIST_H_ */
