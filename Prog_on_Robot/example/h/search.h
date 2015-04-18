/*
 * search.h
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#ifndef SEARCH_H_
#define SEARCH_H_




#include "../h/list.h"
#include "../h/card.h"
#include "../h/settings.h"


logfile logbook;
robot r;



void runbot(robot*);
//void select_direction(robot *r, intersec i);
//void run_robot(robot*);
void dechiff_intersec(intersec*, int);

#endif /* SEARCH_H_ */
