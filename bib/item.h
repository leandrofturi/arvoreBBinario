#ifndef _ITEM_H_
#define _ITEM_H_

#include <stdlib.h>

typedef char* Key;

typedef struct {
    Key id;
    int pos;
} Item;


#define NULLitem NULL

Item* NEWitem(char*, int);

void DELitem(Item*);

Key key(Item*);

int eq(Key, Key);

int less(Key, Key);

#endif
