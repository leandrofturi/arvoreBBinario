#ifndef _ARVOREB_H_
#define _ARVOREB_H_

#include "../bib/item.h"

// B-tree implementation based on Sedgewick (3ed)

typedef struct BTree BTree;


BTree* BTree_init(int);

void BTree_del(BTree*);

Item* BTree_search(BTree*, Key);

void BTree_insert(BTree*, Item*);

void BTree_2file(BTree*, FILE*, FILE*);

#endif