/*
 * list.c
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */


#include <stdlib.h>
#include "../h/list.h"



int comp_p(point p1, point p2) {
	if ((p1.x==p2.x)&&(p1.y==p2.y)) return 1;
	return 0;
}

list_elem push_elem(list_elem *l, list_elem li) {
    while (*l!=NULL) {
        l = &((*l)->next);
    }
    *l = li;

    return li;
}

list_elem pop_elem(list_elem *l, point *p) {
	list_elem next = (*l)->next;
	*p = (*l)->p;
	return next;
}


void push_queue(queue *q, list_elem li) {
	q->end = push_elem(&q->end, li);
}

void pop_queue(queue *q) {
	point p;
	q->start = pop_elem(&q->start, &p);
}

void delete_queue_elem(list_elem *l) {
	if (*l!=NULL) delete_queue_elem(&(*l)->next);
	free(*l);
}

void delete_queue(queue *q) {
	delete_queue_elem(&q->hidden_start);
}

list_elem get_front(queue *q) {
	return q->start;
}

void init_queue(queue* q, point p) {
	list_elem new_elem_ptr = (list_elem) malloc(sizeof(l_elem));
	q->hidden_start = new_elem_ptr;
	q->start = new_elem_ptr;
	q->end = new_elem_ptr;
	new_elem_ptr->p = p;
	new_elem_ptr->next = NULL;
	new_elem_ptr->parent = NULL;
	new_elem_ptr->in = MYBREAK;
}

list_elem make_follower(int dir, point p, list_elem cur) {
	list_elem new_elem_ptr = (list_elem) malloc(sizeof(l_elem));
	new_elem_ptr->p = p;
	new_elem_ptr->next = NULL;
	new_elem_ptr->parent = cur;
	new_elem_ptr->in = dir;
	return new_elem_ptr;
}

void print_back(queue* q, int i) {
	list_elem p;
	if (i==1) {
		p = q->found_elem;
	}
	else {
		p = q->end;
	}

	while (p!=NULL) {
		printf("(%i,%i) ", p->p.x, p->p.y);
		p = p->parent;
	}
	printf("\n");
}



void set_nearfield_ana(analyzer *a, point p, int dir) {
	a->active = 1;
	switch (dir) {
	case MYNORTH:
		a->North.p = p;
		break;
	case MYSOUTH:
		a->South.p = p;
		break;
	case MYWEST:
		a->West.p = p;
		break;
	case MYEAST:
		a->East.p = p;
		break;
	default:
		break;
	}
}

void init_analyzer(analyzer *a) {
	point null_p;
	null_p.x = -133; null_p.y = -133;
	a->North.p = null_p;
	a->South.p = null_p;
	a->West.p = null_p;
	a->East.p = null_p;
	a->North.count = 0;
	a->South.count = 0;
	a->West.count = 0;
	a->East.count = 0;
	a->active = 0;
}



// Stack-Methoden ------------------------------------------------------------------------------------

stack push_stack(stack* s, int x) {
	stack new_elem = (stack) malloc(sizeof(stack_elem));
	new_elem->direction = x;
	new_elem->next = *s;
	return new_elem;
}

stack pop_stack(stack* s, int *x) {
	if (*s==NULL) return NULL;
	stack next = (*s)->next;
	*x = (*s)->direction;
	free(*s);
	return next;
}

void delete_stack(stack* s) {
	if (*s!=NULL) delete_stack(&(*s)->next);
	free(*s);
}


// Logfile- Methoden


void init_logfile(logfile* log) {
	log->start = NULL;
	log->size = 0;
}

void add_to_logfile(logfile *log, int x) {
	log->start = push_stack(&log->start, x);
	log->size++;
}

int pop_from_logfile(logfile *log) {
	int x;
	log->start = pop_stack(&log->start, &x);
	log->size--;
	return x;
}

void delete_logfile(logfile* log) {
	delete_stack(&log->start);
}





