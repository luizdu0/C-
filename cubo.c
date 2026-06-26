// Arquiv SOLUÇÃO DO CUBO
#include <stdio.h>
#include <stdlib.h>
#include "cubo.h"

// FUNÇÕES DE LÓGICA E LEITURA 

int carregarCubo(const char* nome_arq) {
    FILE *arquivo = fopen(nome_arq, "r");
    if (arquivo == NULL) return 0;


    // Ignorar linhas de comentários que iniciam com #
    char c;
    while (fscanf(arquivo, " %c", &c) == 1) {
        if (c == '#') {
            while ((c = fgetc(arquivo)) != '\n' && c != EOF);
        } else {
            ungetc(c, arquivo); // (ungetc) A letra volta para o fluxo para que o fscanf da face leia corretamente
            break; 
        }
    }


    // Lê as 6 faces do txt, percorre a grade 3x3 de cada uma e traduz a letra da cor lida para um número, montando a matriz 3D do cubo
    for (int f = 0; f < 6; f++) {
        char letra_face;
        fscanf(arquivo, " %c", &letra_face); 

        for (int l = 0; l < 3; l++) {
            for (int col = 0; col < 3; col++) {
                char letra_cor;
                fscanf(arquivo, " %c", &letra_cor);
                for(int i = 0; i < 6; i++) {
                    if (letra_cor == letras_cores[i]) {
                        cubo[f][l][col] = i;
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

    if (cuboEstaResolvido()) return 1; 
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

    // Impressão do log de estado inicial
    printf("Instancia lida com sucesso.\nEstado inicial:\n");
    imprimeCubo();

    int seq_face[20], seq_dir[20];
    int limite = 6; // máximo de busca
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

    // Impressão da sequência exata de movimentos e estado final
    printf("\nSequencia de movimentos:\n");
    for(int i = 0; i < total_passos; i++) {
        printf("%s %s\n", nome_faces[seq_face[i]], nome_direcoes[seq_dir[i]]);
    }
    
    printf("\nEstado final:\n");
    imprimeCubo();
    printf("Cubo resolvido:\n\n");

    carregarCubo(argv[1]); // Recarrega o cubo bagunçado do arquivo para mostrar a animação do zero

    // EXIBIÇÃO GRÁFICA
    executaAnimacao(total_passos, seq_face, seq_dir);

    return 0;
}
