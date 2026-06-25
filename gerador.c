// Arquivo gerador
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cubo.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("./gerador <qtd_movimentos> <nome_do_arquivo.txt>\n");
        return 1;
    }


    int movimentos = atoi(argv[1]);
    char* nome_arquivo = argv[2];
    
    srand(time(NULL));
    inicializa_cubo_resolvido();

    // Embaralha usando a CUBINHO
    for (int i = 0; i < movimentos; i++) {
        int face = rand() % 6;
        int dir = rand() % 2;
        rotacao(face, dir);
    }

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo.\n");
        return 1;
    }

    
    fprintf(arquivo, "Cubo embaralhado com %d movimentos\n", movimentos);
    for (int f = 0; f < 6; f++) {
        fprintf(arquivo, "%c\n", nome_faces[f][0]); 
        for (int l = 0; l < 3; l++) {
            for (int c = 0; c < 3; c++) {
                fprintf(arquivo, "%c", letras_cores[cubo[f][l][c]]); 
            }
            fprintf(arquivo, "\n");
        }
    }

    
    fclose(arquivo);
    printf("Arquivo %s gerado\n", nome_arquivo);
    return 0;
}
