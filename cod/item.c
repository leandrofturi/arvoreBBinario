#include <string.h>
#include "../bib/item.h"


Item* NEWitem(char *id, int pos) {
    Item *A = malloc(sizeof(Item));
    int n = strlen(id);
    A->id = malloc(n+1);
    strcpy(A->id, id);
    A->id[n] = '\0';
    A->pos = pos;
    return A;
}

void DELitem(Item *A) {
    free(A->id);
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
