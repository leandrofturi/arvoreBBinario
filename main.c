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

    FILE *f = fopen(filebin, "w");
    /*
    write_record("a", "A", f);
    write_record("b", "B", f);
    write_record("c", "C", f);
    write_record("d", "D", f);
    write_record("e", "E", f);
    write_record("f", "F", f);
    write_record("g", "G", f);
    write_record("h", "H", f);
    write_record("i", "I", f);
    write_record("j", "J", f);
    write_record("k", "K", f);
    write_record("l", "L", f);
    write_record("m", "M", f);
    write_record("n", "N", f);
    write_record("o", "O", f);
    write_record("p", "P", f);*/
    //write_record("q", "Q", f);
    fclose(f);

    processamento(M, filebin);

    return 0;
}
