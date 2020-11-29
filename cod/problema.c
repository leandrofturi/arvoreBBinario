#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../bib/problema.h"
#include "../bib/arvoreB.h"
#include "../bib/binario.h"


void processamento(int M, char *filebin) {
    int on = 1,
        n;
    char cmd[MAX_BUF],
         id[MAX_BUF],
         aux[MAX_BUF],
         *tmp;
    FILE *f, *o;
    Item *item;
    BTree *bt;
    printf("\e[H\e[2J"); // limpar tela

    n = access(filebin, F_OK);
    if(n == -1) { // file doesn't exists
        if((f = fopen(filebin, "w")) == NULL) { // create a file
            printf("ERROR***: can't open %s\n", filebin);
            return;
        }
        else fclose(f);
    }

    if((f = fopen(filebin, "r+")) == NULL) {
        printf("ERROR***: %s not found\n", filebin);
        return;
    }
    bt = BTree_init(M);
    if(n != -1) { // file exist
        n = load(f, bt); // chaves de todos os registros válidos deverão ser inseridas no índice
        printf("%d inserted!\n\n", n);
    }

    while(on) {
        fputs(">> ", stdout);
        fgets(cmd, MAX_BUF, stdin);

        if(strncmp(cmd, "GET", 3) == 0) {
            sscanf(cmd, "GET %s", id);
            item = BTree_search(bt, id);
            if(item != NULLitem) { // se o registro não existir no índice, não mostrar nada na tela
                tmp = walk(item->pos, f);
                if(tmp) {
                    printf("%s: %s\n", id, strchr(tmp, ',') + 1);
                    free(tmp);
                }
            }
        }

        else if(strncmp(cmd, "DELETE", 6) == 0) {
            sscanf(cmd, "DELETE %s", id);
            item = BTree_search(bt, id);
            if(item != NULLitem) // e o identificador não estiver no ídice, nada deve ser feito
                disable(item->pos, f);
        }

        else if(strncmp(cmd, "INSERT", 6) == 0) {
            sscanf(cmd, "INSERT %s %s", id, aux);
            item = BTree_search(bt, id);
            if(item != NULLitem) { // O identificador do cliente está no índice
                tmp = walk(item->pos, f);
                if(tmp) { // e o registro correspondente no arquivo está marcado como ativo
                    disable(item->pos, f); // marque o registro correspondente no arquivo como inativo
                    n = insert(id, aux, f); // escreva o novo registro no final do arquivo
                    item->pos = n; // e atualize o índice para apontar para o novo registro
                    free(tmp);
                }
                else { // mas o registro correspondente no arquivo está marcado como inativo
                    n = insert(id, aux, f); // insira o cliente no final do arquivo
                    item->pos = n; // atualize o índice
                }
            }
            else { // O identificador do cliente não está no índice
                n = insert(id, aux, f); // insira o cliente no final do arquivo
                BTree_insert(bt, NEWitem(id, n)); // e atualize o índice
            }
        }

        else if(strncmp(cmd, "RUNDOWN", 7) == 0) {
            sscanf(cmd, "RUNDOWN %s", aux);
            if((o = fopen(aux, "w")) == NULL)
                printf("ERROR***: can't open %s\n", aux);
            else {
                BTree_2file(bt, f, o);
                fclose(o);
            }
        }

        else if(strncmp(cmd, "STOP", 4) == 0) {
            on = 0;
            // printf("\e[H\e[2J"); // limpar tela
        }
    }

    fclose(f);
    BTree_del(bt);
}