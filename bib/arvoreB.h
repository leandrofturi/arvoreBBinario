#ifndef _ARVOREB_H_
#define _ARVOREB_H_

// B-tree implementation based on Sedgewick (3ed)

typedef int Item;
typedef int Key;
#define key(A) (A)
#define eq(A, B) (key(A) == key(B))
#define less(A, B) (key(A) < key(B))
#define NULLitem -1

typedef struct BTree BTree;


BTree* BTree_init(int);

void BTree_del(BTree*);

Item BTree_search(BTree*, Key);

void BTree_insert(BTree*, Item);


#endif