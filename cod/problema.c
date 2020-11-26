#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../bib/problema.h"
#include "../bib/arvoreB.h"
#include "../bib/binario.h"


void processamento(int M, char *filebin) {
    int on = 1;
    char cmd[MAX_BUF],
         id[MAX_BUF],
         aux[MAX_BUF],
         *tmp;
    FILE *f;
    Item *item;
    BTree *bt;

    if((f = fopen(filebin, "r+")) == NULL) {
        printf("ERROR***: %s not found\n", filebin);
        return;
    }

    bt = BTree_init(M);
    BTree_insert(bt, NEWitem("ed2", 0));
    printf("\e[H\e[2J"); // limpar tela
    while(on) {
        fputs(">> ", stdout);
        fgets(cmd, MAX_BUF, stdin);

        if(strncmp(cmd, "GET", 3) == 0) {
            sscanf(cmd, "GET %s" , id);
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
        }

        else if(strncmp(cmd, "RUNDOWN", 7) == 0) {
            sscanf(cmd, "RUNDOWN %s", aux);
        }

        else if(strncmp(cmd, "STOP", 4) == 0) {
            on = 0;
            printf("\e[H\e[2J"); // limpar tela
        }
    }

    fclose(f);
    BTree_del(bt);
}