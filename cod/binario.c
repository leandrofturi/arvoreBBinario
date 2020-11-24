#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "../bib/binario.h"


void write_record(char *identificador, char *valor, FILE *f) {
    int n = strlen(identificador) + strlen(valor) + 1;
    int flag = 1;
    char v = ',';
    fwrite(&n, 4, 1, f); // 4 bytes com valor de n
    fwrite(&flag, 1, 1, f); // Esse registro é válido
    fwrite(identificador, 1, strlen(identificador), f); // Escreve identificador
    fwrite(&v, 1, 1, f); // Escreve a vírgula
    fwrite(valor, 1, strlen(valor), f); // Escreve o valor
}


/*
    Tests

int main(int argc, char *argv[]) {
    FILE *f = fopen("out.txt", "w");
    write_record("ed2", "facil", f);
    write_record("paa", "deboa", f);
    write_record("tc", "suave", f);
    write_record("cd", "jafoi", f);
    //hexdump -C out.txt
}
*/