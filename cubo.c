// Arquiv SOLUÇÃO DO CUBO
#include <stdio.h>
#include <stdlib.h>
#include "cubo.h"

// FUNÇÕES DE LÓGICA E LEITURA 

int carregarCubo(const char* nome_arq) {
    FILE *arquivo = fopen(nome_arq, "r");
    if (arquivo == NULL) return 0;

    char buffer[100];
    fgets(buffer, sizeof(buffer), arquivo); 

    for (int f = 0; f < 6; f++) {
        char letra_face;
        fscanf(arquivo, " %c", &letra_face); 

        for (int l = 0; l < 3; l++) {
            for (int c = 0; c < 3; c++) {
                char letra_cor;
                fscanf(arquivo, " %c", &letra_cor);
                for(int i = 0; i < 6; i++) {
                    if (letra_cor == letras_cores[i]) {
                        cubo[f][l][c] = i;
                        break;
                    }
                }
            }
        }
    }
    fclose(arquivo);
    return 1;
}

// Algoritmo de Backtracking
int resolve(int qtd_atual, int limite, int* passos_face, int* passos_direcao) {
    if (cubo_esta_resolvido()) return 1; 
    if (qtd_atual >= limite) return 0; 

    for (int f = 0; f < 6; f++) {
        for (int d = 0; d < 2; d++) {
            rotacao(f, d); 
            passos_face[qtd_atual] = f;
            passos_direcao[qtd_atual] = d;
            
            if (resolve(qtd_atual + 1, limite, passos_face, passos_direcao)) {
                return 1; 
            }
            
            // Backtracking: Desfaz o movimento
            int direcao_oposta = (d == HORARIO) ? ANTIHORARIO : HORARIO;
            rotacao(f, direcao_oposta); 
        }
    }
    return 0;
}


//  FUNÇÃO PRINCIPAL

int main(int argc, char** argv) {
    // 1. Validação do terminal
    if (argc != 2) {
        printf("Uso: ./cubo <arquivo_do_cubo.txt>\n");
        return 1;
    }

    if (!carregarCubo(argv[1])) {
        printf("Erro: Nao foi possivel abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    int seq_face[20], seq_dir[20];
    int limite = 6; // máximO de busca
    int resolvido = 0;
    int total_passos = 0;

    // Busca a solução no background primeiro
    printf("Calculando a solucao (limite de %d movimentos)... Aguarde\n", limite);
    for (int i = 1; i <= limite; i++) {
        if (resolve(0, i, seq_face, seq_dir)) {
            total_passos = i;
            resolvido = 1;
            break;
        }
    }

    if (!resolvido) {
        printf("Nao foi possivel encontrar uma solucao em ate %d passos para esta instancia\n", limite);
        return 1;
    }

    // Recarrega o cubo bagunçado do arquivo para mostrar a animação do zero
    carregarCubo(argv[1]); 

    //EXIBIÇÃO GRÁFICA
    executa_animacao(total_passos, seq_face, seq_dir);

    return 0;
}
