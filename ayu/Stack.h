#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack {
	Int end;
	TYPE arr[MAX_STACK_SIZE];
} Stack;

void Stack_init(Stack* s);
void Stack_clear(Stack* s);
void Stack_push(Stack* s, TYPE val);
TYPE Stack_pop(Stack* s);
Bool Stack_is_empty(Stack* s);

#endif
