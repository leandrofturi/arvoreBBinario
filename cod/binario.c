#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "../bib/binario.h"


// hexdump -C out.txt
void write_record(char *identificador, char *valor, FILE *f) {
    int n = strlen(identificador) + strlen(valor) + 1;
    int flag = 1;
    char v = ',';
    fwrite(&n, 4, 1, f); // 4 bytes com valor de n
    fwrite(&flag, 1, 1, f); // Esse registro é válido
    fwrite(identificador, 1, strlen(identificador), f); // Escreve identificador
    fwrite(&v, 1, 1, f); // Escreve a vírgula
    fwrite(valor, 1, strlen(valor), f); // Escreve o valor
    fflush(f);
}

int load(FILE *f, BTree *bt) {
    char ativo, *data, aux[BLOCK_SIZE];
    int t, tam, pos, c = 0;

    fseek(f, 0, SEEK_SET);
    while(!feof(f)) {
        pos = ftell(f);
        t = fread(&tam, sizeof(int), 1, f);
        if(t <= 0) break;

        fread(&ativo, 1, 1, f);
        fread(aux, 1, tam, f);

        tam = 0;
        while(aux[tam] != ',') tam++;
        data = malloc(tam+1);
        strncpy(data, aux, tam);
        data[tam] = '\0';
        if(ativo == 1) {
            BTree_insert(bt, NEWitem(data, pos));
            c++;
        }
        free(data);
    }
    return c;
}

char* walk(int n, FILE *f) {
    char ativo, *data;
    int tam;
    fseek(f, 0, SEEK_END);
    if(n == ftell(f))
        return NULL;

    fseek(f, n, SEEK_SET);
    fread(&tam, sizeof(int), 1, f);
    fread(&ativo, 1, 1, f);
    if(ativo == 0) // se o registro estiver marcado como inativo no arquivo, não mostrar nada na tela
        return NULL;

    data = malloc(tam+1);
    fread(data, 1, tam, f);
    data[tam] = '\0';

    return data;
}

void disable(int n, FILE *f) {
    int flag = 0;
    fseek(f, n+4, SEEK_SET); // caso o identificador esteja marcado como inativo no arquivo, nada deve ser feito
    fwrite(&flag, 1, 1, f); // caso o identificador esteja no índice e marcado como ativo no arquivo, marque-o como inativo
    fflush(f);
}

int insert(char *chave, char *valor, FILE *f) {
    fseek(f, 0, SEEK_END);
    int n = ftell(f);
    write_record(chave, valor, f); // insira o cliente no final do arquivo;
    fflush(f);
    return n;
}
