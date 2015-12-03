#ifndef __TTABLE_H__
#define __TTABLE_H__

typedef struct Entry {
	char depth;
	char value_type;
	Int value;
	Move move;
	UInt lock;
} Entry;

void TTable_init();
Entry* TTable_lookup(Position* pos);
void TTable_store(Position* pos, Entry* e);

#endif
