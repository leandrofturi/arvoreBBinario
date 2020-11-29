#ifndef _BINARIO_H_
#define _BINARIO_H_

#include <stdio.h>
#include "arvoreB.h"

#define BLOCK_SIZE 4096


// Write record
void write_record(char*, char*, FILE*);

// Chaves de todos os registros válidos deverão ser inseridas no índice
int load(FILE*, BTree*);

// Caminha a partir de uma posição do arquivo buscando os dados de uma chave
char* walk(int, FILE*);

// Desativa um cliente
void disable(int, FILE*);

// Insere ao final do arquivo
int insert(char *, char*, FILE*);

#endif
