#include "Common.h"

#include "TTable.h"
#include "Data.h"
#include "Position.h"

static Entry entries[MAX_ENTRIES];

void TTable_init() {
	Int i;
	for (i = 0; i < MAX_ENTRIES; ++i) {
		Entry* e;
		e = &entries[i];
		e->depth = -1;
		e->value_type = INVALID_VALUE;
		e->value = -1;
		e->move = INVALID_MOVE;
		e->lock = 0;
	}
}

Entry* TTable_lookup(Position* pos) {
	UInt h;
	Int i;
	Entry* e;
	h = Position_get_hash(pos);
	i = h & TTABLE_MASK;
	e = &entries[i];
	if (e->lock == Position_get_lock(pos)) {
		return e;
	} else {
		return NULL;
	}
}

void TTable_store(Position* pos, Entry* e) {
	UInt h;
	Int i;
	Entry* entry;
	h = Position_get_hash(pos);
	i = h & TTABLE_MASK;
	entry = &entries[i];
	if ((entry->depth < e->depth) ||
	        ((entry->depth == e->depth) && (e->value_type == EXACT))) {
		memcpy(entry, e, sizeof(Entry));
	}
}
