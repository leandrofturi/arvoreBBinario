#include <stdio.h>
#include <stdlib.h>
#include "bib/arvoreB.h"


int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Usage: ./trab3 M <file>\n");
        return 0;
    }

    int M = atoi(argv[1]);
    char *file = argv[2];

    BTree *bt = BTree_init(M);
    BTree_insert(bt, NEWitem("mariah", 5));
    BTree_insert(bt, NEWitem("joa", 8));
    BTree_insert(bt, NEWitem("joana", 5));
    BTree_insert(bt, NEWitem("joaquina", 8));
    BTree_insert(bt, NEWitem("fabia", 5));
    BTree_insert(bt, NEWitem("joapa", 8));

    BTree_insert(bt, NEWitem("mariaha", 5));
    BTree_insert(bt, NEWitem("joaa", 8));
    BTree_insert(bt, NEWitem("joanaa", 5));
    BTree_insert(bt, NEWitem("joaquinaa", 8));
    BTree_insert(bt, NEWitem("fabiaa", 5));
    BTree_insert(bt, NEWitem("joapaa", 8));

    BTree_insert(bt, NEWitem("marbiah", 5));
    BTree_insert(bt, NEWitem("jboa", 8));
    BTree_insert(bt, NEWitem("joabna", 5));
    BTree_insert(bt, NEWitem("joabquina", 8));
    BTree_insert(bt, NEWitem("fabbia", 5));
    BTree_insert(bt, NEWitem("jobapa", 8));
    
    printf("%d\n", BTree_search(bt, "mariah")->pos);
    BTree_del(bt);

    return 0;
}
