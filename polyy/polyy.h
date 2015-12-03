#ifndef __POLYY__
#define __POLYY__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstring>

#define N 106
#define OO 1000000

//this the maximum trees to allocate on monte carlo simulations
#define MAX_TREES 60000

//this is the corners mask
//every field in the board have field_mask value depending on
//how many sides it belongs to
#define MASK_CORNER_1 17
#define MASK_CORNER_2 3
#define MASK_CORNER_3 6
#define MASK_CORNER_4 12
#define MASK_CORNER_5 24

//the game is into 4 phases every one with a limit of simulations
// & maximum of iterations
//whenever number of simulations is less than limit(phase)  
//you have a maximum of iterations(phase) to do
#define PHASE_1_LIMIT (400000) 
#define PHASE_1_ITERATIONS (40000)

#define PHASE_2_LIMIT (600000) 
#define PHASE_2_ITERATIONS (20000)

#define PHASE_3_LIMIT (700000)
#define PHASE_3_ITERATIONS (10000)

#define PHASE_4_LIMIT 
#define PHASE_4_ITERATIONS (5000)

#define UCTK 0.1
#define OPENING_MOVES 20

//#define DEBUGGING

typedef unsigned char Player;
typedef int Move;

typedef double Layer[N + 1];
typedef Move MoveList[N + 1];

//define the neighbours of a field as a zero terminated list
extern int neighbours[N + 1][7];

//define the joint of a field that is the field that has 2 neighbours with this field
//as (the_field, neighbours_1, neighbours_2)
extern int joint[N + 1][30];

//define the mask of a field
extern int field_mask[N + 1];

//define the sides fields
extern int sides[6][8];

//define the sides mask
extern int side_mask[6];

//define the rotation matrix
extern int rotate[107];

//define the symmetry matrix
extern int sym[107];

//define the attack of a joint field connection as (first_field, second_field, where_to_protect)
extern int attack[107][20];

//define the weak field with a field f that shares only one neighbour with the field
//as (the_field, the_neighbour)
extern int weak[N + 1][20];

//max iterations for a move search
extern int MAX_ITERATIONS;

//max visits for a single move
extern int MAX_VISITS;

//corners 
extern int CORNER_1;
extern int CORNER_2;
extern int CORNER_3;
extern int CORNER_4;
extern int CORNER_5;
extern Player WHITE;
extern Player BLACK;
extern Player NONE;
extern Move SWAP_MOVE;
extern Move UNKNOWN_MOVE;

//exploration bonus for handle the trade between exploration and exploitation
//not used in the end just AMAF biasing
extern double EXPLORATION_BONUS[MAX_TREES];

using namespace std;

#endif
