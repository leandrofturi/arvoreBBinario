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

    BTree_del(bt);

    return 0;
}
