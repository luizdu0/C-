#include <stdio.h>
#include <stdlib.h>
#include <time.h> // bibilioteca para gerar numeros aleatorios


// deixar fora da main, para ler o arquivo, rotacionar, checar se está resolvido

// definição
enum Cores { AMARELO, VERDE, VERMELHO, LARANJA, BRANCO, AZUL };
enum Rotacao { NORTE, SUL, LESTE, OESTE };
enum Direcao { HORARIO, ANTIHORARIO };
enum Face { CIMA, BAIXO, ESQUERDA, DIREITA, FRENTE, TRAS };

// 6 faces, cada uma com 3 linhas e 3 colunas de adesivos
int faces[6][3][3];

int main(){
    
int n, i, f, linha, coluna, cor_sorteada;

    char nome_arquivo[100];
    
    // U = Up (Cima), D = Down (Baixo), L = Left (Esq.), R = Right (Dir.), F = Front (Frente), B = Back (Atrás)
    char nomes_faces[6] = {'U', 'D', 'L', 'R', 'F', 'B'};
    
    // Y = Yellow (Amarelo), G = Green (Verde), R = Red (Vermelho), O = Orange (Laranja), W = White (Branco), B = Blue (Azul)
    char letras_cores[6] = {'Y', 'G', 'R', 'O', 'W', 'B'};

    // inicializa gerador de números aleatórios usando o relógio do pc (stdlib.h e time.h)
    srand(time(NULL));


    // 1. Pergunta ao usuário quantos arquivos gerar 
    printf("Quantos arquivos de cubos embaralhados voce quer gerar (N)?");
     scanf("%d", &n);

    // 2. Laço principal para criar os N arquivos
    for (i = 1; i <= n; i++) {
        
        // sprintf escreve o titulo dos arq, (ex: cubo_1.txt, cubo_2.txt)
        sprintf(nome_arquivo, "cubo_%d.txt", i);

        // abre o arquivo para escrita ("w" = write)
         FILE *arquivo = fopen(nome_arquivo, "w");

        // se abriu corretamente
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo %s!\n", nome_arquivo);
        } else {
            
            // fprint escreve no inicio do arquivo cubo tal...
            fprintf(arquivo, "# Cubo aleatorio %d\n", i);
            
            
            // 3. Preenche as 6 faces do cubo no arquivo
            for (f = 0; f < 6; f++) {
                // escreve a letra da face (U, D, L...)
                fprintf(arquivo, "%c\n", nomes_faces[f]); // printa a face com base no vet[f]
                
                // preenche as 3 linhas e 3 colunas de cores
                for (linha = 0; linha < 3; linha++) {
                    for (coluna = 0; coluna < 3; coluna++) {
                        cor_sorteada = rand() % 6; // rand da um número aleatorio e o resto dessa divisão por 6 SEMPRE será 0, 1, 2, 3, 4, 5
                        fprintf(arquivo, "%c", letras_cores[cor_sorteada]); // imprime na linha e coluna uma cor do vet de cores com base no rand de 0 a 5 
                    }
                    
                    // quebra a linha para continuar a próxima fileira de adesivos da mesma face
                    fprintf(arquivo, "\n");
                }

            
            
            
            
            printf("Arquivo %s gerado com sucesso.\n", nome_arquivo);
            fclose(arquivo);
        }
<<<<<<< HEAD
    }
=======
        cor++;
        }
       int resulado = embaralhador(cubo);

        if(resulado == 1){
            printf("Cubo embaralhado com sucesso!\n");
        } else {
            printf("Erro ao embaralhar o cubo.\n");
        }
>>>>>>> 31d3288b92efd0787d32c385c38c2a5a58e4a159

    return 0;    
    
    

}