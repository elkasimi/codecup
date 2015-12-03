#include "Common.h"

#include "HashSet.h"
#include "Tree.h"

static TreeIterator* array[HASH_SET_SIZE];

static UInt HashSet_index(Tree* t) {
	UInt l = t->hash >> 16;
	UInt r = t->hash & 0xffff;
	UInt h = l ^ r;
	h &= HASH_SET_MASK;
	return h;
}

void HashSet_store(Tree* t) {
	UInt h = HashSet_index(t);
	TreeIterator* it = (TreeIterator*)malloc(sizeof(TreeIterator));
	it->next = array[h];
	it->tree = t;
	array[h] = it;
}

void HashSet_remove(Tree* t) {
	UInt h = HashSet_index(t);
	TreeIterator* it;
	TreeIterator* last_it = NULL;
	for (it = array[h]; it != NULL; it = it->next) {
		if (it->tree == t) {
			if (last_it == NULL) {
				array[h] = it->next;
			} else {
				last_it->next = it->next;
			}
			free(it);
			break;
		}
		last_it = it;
	}
}

TreeIterator* HashSet_find(Tree* t) {
	UInt h = HashSet_index(t);
	TreeIterator* it = array[h];
	return it;
}
