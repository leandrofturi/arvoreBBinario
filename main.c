#include <stdio.h>
#include <stdlib.h>
#include "bib/problema.h"
#include "bib/binario.h"


int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Usage: ./trab3 M <file>\n");
        return 0;
    }

    int M = atoi(argv[1]);
    char *filebin = argv[2];

    processamento(M, filebin);

    return 0;
}
