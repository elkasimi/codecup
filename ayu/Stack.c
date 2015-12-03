#include "Common.h"

#include "Stack.h"

void Stack_init(Stack* s) {
	s->end = 0;
}

void Stack_clear(Stack* s) {
	s->end = 0;
}

void Stack_push(Stack* s, TYPE val) {
	s->arr[s->end] = val;
	s->end += 1;
}

TYPE Stack_pop(Stack* s) {
	s->end -= 1;
	TYPE val = s->arr[s->end];
	return val;
}

Bool Stack_is_empty(Stack* s) {
	return (s->end == 0);
}
