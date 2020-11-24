#include <stdlib.h>
#include <stdio.h>
#include "../bib/arvoreB.h"


typedef struct STnode* link;
typedef struct {
    Key key;
    union {
        link next;
        Item item;
    } ref;
} entry;

struct STnode {
    entry *b; // altereted
    int m;
};

struct BTree {
    link head;
    int H, N, M; // altereted
};


static link NEW(int M) { // altereted
    link x = malloc(sizeof(struct STnode));
    x->b = malloc(M*sizeof(entry));
    x->m = 0;
    return x;
}

BTree* BTree_init(int M) {
    if(M < 4) { // altereted
        printf("ERROR***: invalid M\n");
        return NULL;
    }

    BTree *bt = malloc(sizeof(BTree));
    bt->head = NEW(M);
    bt->H = 0;
    bt->N = 0;
    bt->M = M;
    return bt;
}

static void delR(link h, int H) { // altereted
    int j;
    if(H == 0)
        return;

    if(H != 0)
        for(j = 0; j < h->m; j++) {
            delR(h->b[j].ref.next, H-1);
            free(h->b[j].ref.next->b);
            free(h->b[j].ref.next);
        }
}

void BTree_del(BTree *bt) { // altereted
    if(bt == NULL) {
        printf("ERROR***: NULL BTree\n");
        return;
    }

    delR(bt->head, bt->H);
    free(bt->head->b);
    free(bt->head);
    free(bt);
}

static Item searchR(link h, Key v, int H) {
    int j;
    if(H == 0)
        for(j = 0; j < h->m; j++)
            if(eq(v, h->b[j].key))
                return h->b[j].ref.item;
    if(H != 0)
        for(j = 0; j < h->m; j++)
            if((j+1 == h->m) || less(v, h->b[j+1].key))
                return searchR(h->b[j].ref.next, v, H-1);
    return NULLitem;
}

Item BTree_search(BTree *bt, Key v) {
    if(bt == NULL) { // altereted
        printf("ERROR***: NULL BTree\n");
        return NULLitem;
    }
    return searchR(bt->head, v, bt->H);
}

static link split(link h, int M) {
    int j;
    link t = NEW(M);
    for(j = 0; j < M/2; j++)
        t->b[j] = h->b[M/2+j];
    h->m = M/2;
    t->m = M/2;
    return t;
}

static link insertR(link h, Item item, int H, int M) {
    int i, j;
    Key v = key(item);
    entry x;
    link t, u;

    x.key = v;
    x.ref.item = item;

    if(H == 0)
        for(j = 0; j < h->m; j++)
            if(less(v, h->b[j].key))
                break;
    if(H != 0)
        for(j = 0; j < h->m; j++)
            if((j+1 == h->m) || less(v, h->b[j+1].key)) {
                t = h->b[j++].ref.next;
                u = insertR(t, item, H-1, M);
                if(u == NULL)
                    return NULL;
                x.key = u->b[0].key;
                x.ref.next = u;
                break;
            }
    for(i = (h->m)++; i > j; i--)
        h->b[i] = h->b[i-1];
    h->b[j] = x;
    if(h->m < M)
        return NULL;
    else
        return split(h, M);
}

void BTree_insert(BTree *bt, Item item) {
    if(bt == NULL) { // altereted
        printf("ERROR***: NULL BTree\n");
        return;
    }

    link t, u = insertR(bt->head, item, bt->H, bt->M);
    if(u == NULL)
        return;

    t = NEW(bt->M);
    t->m = 2;
    t->b[0].key = bt->head->b[0].key;
    t->b[0].ref.next = bt->head;
    t->b[1].key = u->b[0].key;
    t->b[1].ref.next = u;
    bt->head = t;
    bt->H++;
}


/*
    Tests
int main(int argc, char *argv[]) {
    BTree *bt = BTree_init(4);
    for(int i = 0; i < 10; i++)
        BTree_insert(bt, i);
    for(int i = 0; i < 10; i++)
        printf("%d\n", BTree_search(bt, i));
    printf("%d\n", BTree_search(bt, 11));
    BTree_del(bt);
}
*/