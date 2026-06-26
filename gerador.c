// Arquivo gerador
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cubo.h"


// Espera 3 coisas: ./gerador, a quantidade de movimentos e o nome do arquivo
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("./gerador <quantidade_de_arquivos>\n");
        return 1;
    }
    int n_arquivos = atoi(argv[1]); // Quantidade de arquivos N que o usuario digitou
    
    srand(time(NULL));

// Criando N arquivos e resolvendo
for (int i = 1; i <= n_arquivos; i++) {
 char nome_arq[50];
        sprintf(nome_arq, "cubo%d.txt", i);
        inicializaCuboResolvido();

    // Embaralha usando a CUBINHO
   int movimentos = 15 + (rand() % 16);  // Sorteia aleatoriamente entre 15 e 30 movimentos para cada arquivo gerado
   for (int m = 0; m < movimentos; m++) {
            int face = rand() % 6;
            int dir = rand() % 2;
            rotacao(face, dir);
        }

    FILE *arquivo = fopen(nome_arq, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo\n");
        return 1;
    }

    
    // Escreve as 6 faces no arquivo
    fprintf(arquivo, "# Cubo embaralhado com %d movimentos\n", movimentos);
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
    printf("Arquivo %s gerado\n", nome_arq);
}
    return 0;
}
