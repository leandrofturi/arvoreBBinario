#ifndef _BINARIO_H_
#define _BINARIO_H_

#include "stdio.h"

#define BLOCK_SIZE 4096

// Write record
void write_record(char*, char*, FILE*);

// Caminha a partir de uma posição do arquivo buscando os dados de uma chave
char* walk(int, FILE*);

// Desativa um cliente
void disable(int, FILE*);

#endif