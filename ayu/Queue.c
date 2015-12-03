#include "Common.h"

#include "Queue.h"

void Queue_init(Queue* q) {
	q->start = 0;
	q->end = 0;
}

void Queue_clear(Queue* q) {
	q->start = 0;
	q->end = 0;
}

void Queue_push(Queue* q, TYPE val) {
	q->arr[q->end] = val;
	q->end += 1;
	q->end &= MAX_QUEUE_SIZE - 1;
}

TYPE Queue_pop(Queue* q) {
	TYPE val = q->arr[q->start];
	q->start += 1;
	q->start &= MAX_QUEUE_SIZE - 1;
	return val;
}

Bool Queue_is_empty(Queue* q) {
	return (q->start == q->end);
}
