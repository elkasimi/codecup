#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>

#if WINDOWS_VERSION
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#endif

#define EQUAL_STRING(s1, s2) (strcmp((s1), (s2)) == 0)

#define READ_STRING(s)			\
do {							\
	Int rc = scanf("%s", (s));	\
	assert(rc == 1);			\
} while (0)

#define FROM(move) (move & 0x7f)
#define TO(move) ((move >> 7) & 0x7f)
#define MAKE_MOVE(f, t) ((f) | ((t) << 7))

#define INVALID_MOVE ((Move)0)

#define WHITE 0
#define BLACK 1
#define NONE 2

#define TRUE 1
#define FALSE 0

#define N 11
#define NXN 121

#define END (-1)

#define MAX_MOVES 100

//Group defines
#define MAX_PLAYER_GROUPS 30
#define MAX_GROUPS 60
#define MAX_GROUP_MEMBERS 30

//Queue defines
#define TYPE Int
#define MAX_QUEUE_SIZE 1024
#define MAX_STACK_SIZE 1024

#define HASH_SET_SIZE 8192
#define HASH_SET_MASK 8191
#define SAMPLES	10

#define OPENING_MOVES 20
#define CRITICAL_CHECK_LIMIT 0

typedef unsigned char Bool;

typedef unsigned char Player;

typedef unsigned int Move;

typedef unsigned int UInt;

typedef int Int;

typedef Move MoveList[MAX_MOVES];

typedef char String[1024];

typedef unsigned long long BitMap;

typedef unsigned long long ULong64;

typedef double Real;

typedef struct Group Group;

typedef struct Position Position;

#define AYU_VERSION_DEBUG 1

#if AYU_VERSION_DEBUG
#define AYU_ASSERT(cond) assert((cond))
#else
#define AYU_ASSERT(cond)
#endif

#define OO 1000000000

#if WINDOWS_VERSION
#else
#endif

#define CRITICAL_GROUP_COUNT 3

#define USE_HASH_SET 1
#define USE_OPENING_BOOK 1
#define USE_TIME_LIMIT 1
#define USE_LAST_GOOD_REPLY 0
#define USE_OUTSIDE_INSIDE_MOVES_BIASING 0
#define USE_SEPARATING_MOVES_BIASING 0
#define USE_LAST_MOVE_BIASING 0

#define MAX_ITERATIONS	(200000 / SAMPLES)
#define MAX_VERIFICATION_ITERATIONS (1000 / SAMPLES)

#endif
