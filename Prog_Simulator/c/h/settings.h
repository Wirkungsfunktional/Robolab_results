/*
 * settings.h
 *
 *  Created on: 23.03.2015
 *      Author: mk
 */

#ifndef C_H_SETTINGS_H_
#define C_H_SETTINGS_H_



#define MYNORTH 1
#define MYSOUTH 2
#define MYWEST 3
#define MYEAST 4
#define MYBREAK 5

#define No 16
#define So 32
#define NS 48
#define We 64
#define NW 80
#define SW 96
#define NSW 112
#define Ea 128
#define NE 144
#define ES 160
#define NES 176
#define EW 192
#define NEW 208
#define ESW 224
#define NESW 240

#define TOKEN 3


#define ROW 17
#define COL 17
#define hrow (ROW-1)/2
#define hcol (COL-1)/2
#define START ROW*hcol + hcol
#define WALL_N 1000
#define WALL_S 1001
#define WALL_E 1002
#define WALL_W 1003
#define SIZEX 7
#define SIZEY 8

#define SPEED 35



#endif /* C_H_SETTINGS_H_ */
