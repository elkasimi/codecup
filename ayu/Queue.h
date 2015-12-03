#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct Queue {
	Int start;
	Int end;
	TYPE arr[MAX_QUEUE_SIZE];
} Queue;

void Queue_init(Queue* q);
void Queue_clear(Queue* q);
void Queue_push(Queue* q, TYPE val);
TYPE Queue_pop(Queue* q);
Bool Queue_is_empty(Queue* q);

#endif
