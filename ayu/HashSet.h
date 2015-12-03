#ifndef __HASHSET_H__
#define __HASHSET_H__

typedef struct Tree Tree;
typedef struct TreeIterator TreeIterator;

void HashSet_store(Tree* t);
void HashSet_remove(Tree* t);
TreeIterator* HashSet_find(Tree* t);

#endif
