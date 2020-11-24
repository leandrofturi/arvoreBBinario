#include <string.h>
#include "../bib/item.h"


Item* NEWitem(char *id, int pos) {
    Item *A = malloc(sizeof(Item));
    A->id = id;
    A->pos = pos;
    return A;
}

void DELitem(Item *A) {
    //free(A->id);
    free(A);
}

Key key(Item *A) {
    return A->id;
}

int eq(Key A, Key B) {
    return strcmp(A, B) == 0;
}

int less(Key A, Key B) {
    return strcmp(A, B) < 0;
}
